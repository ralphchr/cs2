package booksBorrowing

import java.time.LocalDate

interface BorrowableItem{
    fun uniqueItemId(): Int
    fun commonName(): String
    fun borrowPeriod(): Int
}

class Page(
    private val sectionHeader: String,
    private val body: String
)

class Book(
    private val bookId: Int,
    private val title: String,
    private val author: String,
    private val publishDate: LocalDate,
    private val pages: List<Page>
) : BorrowableItem{

    public fun coverInfo(): String{
        return "$title by $author"
    }

    override fun uniqueItemId(): Int{
        return bookId
    }

    override fun commonName(): String{
        return coverInfo()
    }

    override fun borrowPeriod(): Int{
        return 7 }
}

class Periodical(
    private val periodicalId: Int,
    private val title: String,
    private val issue: LocalDate,
    private val pages: List<Page>
) : BorrowableItem{

    override fun uniqueItemId(): Int{
        return periodicalId
    }

    override fun commonName(): String{
        return "$title issue: ${issue.year}-${issue.monthValue}-${issue.dayOfMonth}"
    }

    override fun borrowPeriod(): Int{
        return 1
    }
}

class PC(private val pcID: Int) : BorrowableItem{

    override fun uniqueItemId(): Int{
        return pcID

    }

    override fun commonName(): String{
        return "PC$pcID" }

    override fun borrowPeriod(): Int{
        return 0

    }
}

class LibraryCard(
    private val idNumber: Int,
    private val name: String,
    private val borrowedItems: MutableMap<BorrowableItem, LocalDate>
){

    public fun borrowItem(item: BorrowableItem, date: LocalDate){
        borrowedItems[item] = date
    }

    public fun borrowerReport(): String{
        var r = "$name\n"

        for ((item, date) in borrowedItems){
            r += "${item.commonName()}, borrow date: $date\n" }

        return r

    }

    public fun returnItem(b: BorrowableItem){
        borrowedItems.remove(b) }

    private fun daysOverdue(b: BorrowableItem, today: LocalDate): Int{
        val borrowedDate = borrowedItems[b]

        if (borrowedDate == null){
            return 0 }

        var date = borrowedDate.plusDays(b.borrowPeriod().toLong())
        var days = 0

        while (date <today){
            days = days + 1
            date = date.plusDays(1L)

        }

        return days

    }

    public fun penalty(b: BorrowableItem, today: LocalDate): Float{
        val days = daysOverdue(b, today)
        val dailyRate = 3.5f

        val amount = days * dailyRate

        return amount
    }