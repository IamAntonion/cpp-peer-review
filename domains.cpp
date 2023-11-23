#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
public:
    // разработайте класс домена

    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
    Domain(const std::string& domain) {
        
        std::string add_dot = "." + domain;
        std::reverse(add_dot.begin(), add_dot.end());
        
        domain_title_ = add_dot;
    }
    
    // разработайте operator==
    bool operator==(const Domain& other_domain) const {
        
        return std::lexicographical_compare(domain_title_.begin(),
                                            domain_title_.end(),
                                            other_domain.domain_title_.begin(),
                                            other_domain.domain_title_.end());
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& other_domain) const {
        
        if (!(other_domain.domain_title_.size() > domain_title_.size())) {
            
            if (std::equal(other_domain.domain_title_.begin(), 
                           other_domain.domain_title_.end(), 
                           domain_title_.begin())) {
                return true;
                
            } else {
                return false;
            }
            
        } else {
            return false;
        }
    }
    
    std::string GetDomain() const {return domain_title_;}
private:
    std::string domain_title_;
};

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template<typename Iterator>
    DomainChecker(const Iterator start, const Iterator end) {
 
        std::vector<Domain> domains(start, end);
        
        std::sort(domains.begin(), domains.end(),
               [](const Domain& lhs, const Domain& rhs) {return lhs == rhs;});
 
        Iterator unique_domains_it = std::unique(domains.begin(), domains.end(),
                                              [](const Domain& lhs, const Domain& rhs) {return rhs.IsSubdomain(lhs);});
        
        domains.erase(unique_domains_it, domains.end());        
        forbidden_ = domains;
    }

    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& domain_to_check) {
        
        if (forbidden_.size()) {          
            std::vector<Domain>::iterator domain_pos_it = std::upper_bound(forbidden_.begin(), 
                                                                           forbidden_.end(), 
                                                                           domain_to_check,
                                                                        [](const Domain& lhs, const Domain& rhs) {
                                                                             return lhs.GetDomain() < rhs.GetDomain();
                                                                        });
 
            if (forbidden_.begin() == domain_pos_it) {
                return domain_to_check.IsSubdomain(forbidden_[domain_pos_it - forbidden_.begin()]);
 
            } else {
                return domain_to_check.IsSubdomain(forbidden_[domain_pos_it - forbidden_.begin() - 1]);
                
            }
            
        } else {
           return false; 
        }
    }
private:
    std::vector<Domain> forbidden_;
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
const std::vector<Domain> ReadDomains(std::istream& input, size_t amount) {
    
    std::vector<Domain> domains;
    std::string line;
    
    for (size_t i = 0; i < amount; ++i) {
        
        getline(input, line);
        domains.push_back(line);
    }
    
    return domains;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}
