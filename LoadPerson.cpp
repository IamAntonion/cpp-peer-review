// функция очень большая, необходимо разделить на функции поменьше
// 
// 
// 

struct TimeOutInMilliseconds {
    int time_out;
};

struct DBSettings {
    std::string db_name;
    TimeOutInMilliseconds db_connection_timeout;
    bool db_allow_exceptions;
    DBLogLevel db_log_level;
};

struct PersonFilter {
    int min_age;
    int max_age;
    string name_filter;
}

DBHandler ConnectToDatabase(const DBConnector& connector, const std::string& db_name, int db_connection_timeout) {
    if (db_name.starts_with("tmp."s)) {
        return connector.ConnectTmp(db_name, db_connection_timeout);
    } else {
        return connector.Connect(db_name, db_connection_timeout);
    }
}

std::string GenerateQuery(int min_age, 
                          int max_age, 
                          const std::string& name_filter) {
    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << min_age
              << " and "s << max_age
              << " and Name like '%"s << db.Quote(name_filter) << "%'"s;
    return query_str.str();
}

vector<Person> LoadPersons(const DBSettings& db_settings, 
                           const PersonFilter& person_filter) {
    DBConnector connector(db_settings.db_allow_exceptions, db_settings.db_log_level);

    DBHandler db = ConnectToDatabase(connector, person_filter.db_name, person_filter.db_connection_timeout.time_out);

    if (!db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    DBQuery query(GenerateQuery(min_age, max_age, name_filter));

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back(name, age);
    }
    return persons;
} 