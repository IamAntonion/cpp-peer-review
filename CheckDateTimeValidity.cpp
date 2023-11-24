// можно вынести переменную month_lengths за приделы функции и сделать глобальной
// проверку на високосный год проводить внутри функции

const array month_lengths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool IsLeapYear(int year) {
    return (year % 4 == 0) && !(year % 100 == 0 && year % 400 != 0);
}

template<typename T>
void CheckValidity(const T& verifiable, const int& min_n, const int& max_n, const string& str) {
    if (verifiable < min_n) {
        throw domain_error(str + "is too small"s);
    }
    if (verifiable > max_n) {
        throw domain_error(str + " is too big"s);
    }
}

void CheckDateTimeValidity(const DateTime& dt) {
    const bool is_leap_year = IsLeapYear(dt.year);
    CheckValidity(dt.year, 1, 9999, "year");
    CheckValidity(dt.month, 1, 12, "month");
    CheckValidity(dt.day, 1, month_lengths[dt.month - 1] + (dt.month == 2 && is_leap_year), "day");
    CheckValidity(dt.hour, 0, 23, "hour");
    CheckValidity(dt.minute, 0, 59, "minute");
    CheckValidity(dt.second, 0, 59, "second");
} 