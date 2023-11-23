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
    if (dt.year < 1) {
        throw domain_error("year is too small"s);
    }
    if (dt.year > 9999) {
        throw domain_error("year is too big"s);
    }

    if (dt.month < 1) {
        throw domain_error("month is too small"s);
    }
    if (dt.month > 12) {
        throw domain_error("month is too big"s);
    }

    const bool is_leap_year = IsLeapYear(dt.year);

    if (dt.day < 1) {
        throw domain_error("day is too small"s);
    }
    if (dt.day > month_lengths[dt.month - 1] + (dt.month == 2 && is_leap_year)) {
        throw domain_error("day is too big"s);
    }

    if (dt.hour < 0) {
        throw domain_error("hour is too small"s);
    }
    if (dt.hour > 23) {
        throw domain_error("hour is too big"s);
    }

    if (dt.minute < 0) {
        throw domain_error("minute is too small"s);
    }
    if (dt.minute > 59) {
        throw domain_error("minute is too big"s);
    }

    if (dt.second < 0) {
        throw domain_error("second is too small");
    }
    if (dt.second > 59) {
        throw domain_error("second is too big"s);
    }
} 