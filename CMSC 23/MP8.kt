class InvalidAmountError(message: String) : Exception(message)
class InsufficientFundsError(message: String) : Exception(message)
class CreditLimitError(message: String) : Exception(message)
class InactiveAccountError(message: String) : Exception(message)
class NotAllowedError(message: String) : Exception(message)
class AccountNotFoundError(message: String) : Exception(message)

fun round2(x: Double): Double = Math.round(x * 100) / 100.0
fun money(x: Double): String = "%,.2f".format(x)

abstract class Account(val number: String, val owner: String, val type: String, startBalance: Double) {

    var balance = startBalance
        protected set
    var isActive = true
        protected set

    fun activate() { isActive = true }
    fun deactivate() { isActive = false }

    abstract fun applyMonthlyChanges()

    open fun deposit(amount: Double) {
        checkAmount(amount)
        receive(amount)
    }

    open fun withdraw(amount: Double) {
        checkAmount(amount)
        checkActive()
        if (amount > balance)
            throw InsufficientFundsError("Insufficient funds: balance ${money(balance)}, requested ${money(amount)}")
        balance = round2(balance - amount)
    }

    open fun transfer(target: Account, amount: Double) {
        if (target.number == number)
            throw InvalidAmountError("Cannot transfer to the same account")
        withdraw(amount)
        try {
            target.receive(amount)
        } catch (ex: Exception) {
            receive(amount)
            throw ex
        }
    }

    open fun receive(amount: Double) {
        balance = round2(balance + amount)
    }

    fun info(): String =
        "Owner: $owner\nType: $type\nStatus: ${if (isActive) "Active" else "Inactive"}"

    open fun balanceReport(): String =
        "$type account $number\nBalance: ${money(balance)}"

    protected fun checkAmount(amount: Double) {
        if (amount <= 0)
            throw InvalidAmountError("Amount must be greater than zero")
    }

    protected fun checkActive() {
        if (!isActive)
            throw InactiveAccountError("Account $number is inactive")
    }
}

class PayrollAccount(number: String, owner: String, startBalance: Double) :
    Account(number, owner, "Payroll", startBalance) {

    override fun deposit(amount: Double) {
        throw NotAllowedError("Payroll accounts cannot deposit")
    }

    override fun transfer(target: Account, amount: Double) {
        throw NotAllowedError("Payroll accounts cannot transfer")
    }

    override fun applyMonthlyChanges() {}
}

class DebitAccount(number: String, owner: String, startBalance: Double, val rate: Double = 0.005) :
    Account(number, owner, "Debit", startBalance) {

    companion object {
        const val REQUIRED_BALANCE = 500.0
    }

    override fun applyMonthlyChanges() {
        balance = round2(balance + balance * rate)
        isActive = balance >= REQUIRED_BALANCE
    }
}

class CreditAccount(number: String, owner: String, startBalance: Double,
                    val limit: Double = 10000.0, val rate: Double = 0.02) :
    Account(number, owner, "Credit", startBalance) {

    init {
        if (balance > limit)
            throw CreditLimitError("Starting balance is over the credit limit")
    }

    override fun withdraw(amount: Double) {
        checkAmount(amount)
        checkActive()
        if (balance + amount > limit)
            throw CreditLimitError("Credit limit exceeded: owed ${money(balance)}, limit ${money(limit)}, requested ${money(amount)}")
        balance = round2(balance + amount)
    }

    override fun receive(amount: Double) {
        if (amount > balance)
            throw InvalidAmountError("Payment ${money(amount)} is more than the amount owed ${money(balance)}")
        balance = round2(balance - amount)
    }

    override fun applyMonthlyChanges() {
        balance = round2(balance + balance * rate)
    }

    override fun balanceReport(): String =
        "$type account $number\nOwed: ${money(balance)}\nLimit: ${money(limit)}\nAvailable: ${money(maxOf(limit - balance, 0.0))}"
}

class Bank {
    private val accounts = mutableMapOf<String, Account>()

    fun add(account: Account) {
        accounts[account.number] = account
    }

    fun find(number: String): Account =
        accounts[number] ?: throw AccountNotFoundError("No account $number")

    fun transfer(from: String, to: String, amount: Double) {
        find(from).transfer(find(to), amount)
    }

    fun applyMonthlyChanges() {
        for (account in accounts.values)
            account.applyMonthlyChanges()
    }

    fun showAll() {
        for (account in accounts.values)
            println("${account.number} | ${account.owner} | ${account.type} | ${if (account.isActive) "Active" else "Inactive"} | ${money(account.balance)}")
    }
}

fun attempt(label: String, action: () -> Unit) {
    try {
        action()
        println("OK      $label")
    } catch (ex: Exception) {
        println("DENIED  $label -> ${ex.message}")
    }
}

fun main() {
    val bank = Bank()
    val pay = PayrollAccount("PAY-1", "Alice", 2000.0)
    val deb = DebitAccount("DEB-1", "Alice", 1500.0)
    val cre = CreditAccount("CRE-1", "Alice", 0.0, limit = 5000.0)
    val bob = DebitAccount("DEB-2", "Bob", 600.0)
    for (account in listOf(pay, deb, cre, bob))
        bank.add(account)

    bank.showAll()
    println()
    println(pay.info())
    println()

    println("-- Payroll")
    attempt("payroll withdraw 300") { pay.withdraw(300.0) }
    attempt("payroll deposit 100") { pay.deposit(100.0) }
    attempt("payroll transfer 100 to Bob") { bank.transfer("PAY-1", "DEB-2", 100.0) }
    attempt("debit transfer 200 to payroll") { bank.transfer("DEB-1", "PAY-1", 200.0) }

    println("-- Debit")
    attempt("debit withdraw 5000") { deb.withdraw(5000.0) }
    attempt("debit transfer 100 to Bob") { bank.transfer("DEB-1", "DEB-2", 100.0) }
    attempt("debit deposit -50") { deb.deposit(-50.0) }

    println("-- Credit")
    attempt("credit withdraw 3000") { cre.withdraw(3000.0) }
    attempt("credit withdraw 2500 (over limit)") { cre.withdraw(2500.0) }
    attempt("credit transfer 1000 to Bob") { bank.transfer("CRE-1", "DEB-2", 1000.0) }
    attempt("credit transfer 1500 to Bob (over limit)") { bank.transfer("CRE-1", "DEB-2", 1500.0) }
    attempt("credit deposit 500") { cre.deposit(500.0) }
    attempt("credit deposit 9999 (more than owed)") { cre.deposit(9999.0) }
    println(cre.balanceReport())

    println("-- Monthly changes")
    bank.applyMonthlyChanges()
    bank.showAll()

    println("-- Required balance")
    attempt("Bob withdraws all but 100") { bob.withdraw(bob.balance - 100.0) }
    bank.applyMonthlyChanges()
    println("Bob is ${if (bob.isActive) "Active" else "Inactive"}")
    attempt("Bob withdraws 10") { bob.withdraw(10.0) }
    attempt("Alice sends Bob 600") { bank.transfer("DEB-1", "DEB-2", 600.0) }
    bank.applyMonthlyChanges()
    println("Bob is ${if (bob.isActive) "Active" else "Inactive"}")

    println("-- Activate / deactivate")
    deb.deactivate()
    attempt("Alice debit withdraw 10") { deb.withdraw(10.0) }
    deb.activate()
    attempt("Alice debit withdraw 10") { deb.withdraw(10.0) }
    attempt("transfer to unknown account") { bank.transfer("DEB-1", "XXX", 10.0) }

    println()
    bank.showAll()
}
