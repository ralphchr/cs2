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