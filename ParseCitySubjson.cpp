// зачем отдельно передавать значения одного объекта, если можно переместить весь объект и спрашивать
// значения относительно объекта

void ParseCitySubjson(vector<City>& cities, const Json& json, const Country& country) {
    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();
        cities.push_back({.name = city_obj["name"s].AsString(), 
                          .iso_code = city_obj["iso_code"s].AsString(),
                          .phone_code = country.phone_code + city_obj["phone_code"s].AsString(), 
                          .country_name = country.name, 
                          .country_iso_code = country.iso_code,
                          .time_zone = country.time_zone, 
                          .languages = country.languages});
    }
}

vector<Country> ParseCountryList(const Json& json_lang) {
    std::vector<Country> country_result;
    for (const auto& lang_obj : json_lang.AsList()) {
            country_result.languages.push_back(FromString<Language>(lang_obj.AsString()));
    }
    return country_result;
}

void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            .name = country_obj["name"s].AsString(),
            .iso_code = country_obj["iso_code"s].AsString(),
            .phone_code = country_obj["phone_code"s].AsString(),
            .time_zone = country_obj["time_zone"s].AsString(),
        });
        Country& country = countries.back();
        country = ParseCountryList(country_obj["languages"s]);
        ParseCitySubjson(cities, country_obj["cities"s], countries);
    }
} 
