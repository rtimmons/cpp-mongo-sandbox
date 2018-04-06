#include <utility>
#include <string>
#include <map>
#include <vector>
#include <iostream>

namespace rr {

    class unit {
    public:
        unit(std::string name)
        : name_{std::move(name)} {}
        const std::string& name() {
            return name_;
        }
        bool operator==(const unit& other) const noexcept {
            return this->name_ == other.name_;
        }
        bool operator<(const unit& other) const noexcept {
            return this->name_ < other.name_;
        }
    private:
        std::string name_;
    };

    template <class T>
    class quantities {
    protected:
        using pr = std::pair<const unit&,T>;
        pr from_;
        pr to_;
    public:
        quantities(const unit& from, T from_amt,
                   const unit& to,   T to_amt)
        : from_{pr{from,from_amt}}, to_{pr{to, to_amt}} {}
        bool operator==(const quantities& other) const noexcept {
            return this->from_ == other.from_ &&
                   this->to_ == other.to_;
        }
    };

    template<class T>
    class rate : public quantities<T> {
    public:
        rate(const unit& from, T from_amt,
             const unit& to,   T to_amt)
        : quantities<T>(from, from_amt, to, to_amt) {}
    };

    template<class T>
    class equiv : public quantities<T> {
    public:
        equiv(const unit& from, T from_amt,
              const unit& to,   T to_amt)
        : quantities<T>(from, from_amt, to, to_amt) {}
    };

    template <typename T>
    using upair = std::pair<T,unit>;

    template<typename T>
    using upairs = std::pair<upair<T>, upair<T>>;

    template <typename T>
    using pairs = std::vector<upairs<T>>;

    template <class T>
    class table {
    public:
        table(pairs<T> vals)
        : vals_(std::move(create_map(std::move(vals)))) {}
        std::multimap<unit,equiv<T>> vals_;
    private:
        std::multimap<unit,equiv<T>> create_map(pairs<T> &&pairs) {
            std::multimap<unit,equiv<T>> out;
            for(const auto& pair : pairs) {
                out.insert({pair.first.second, {
                    pair.first.second,
                    pair.first.first,
                    pair.second.second,
                    pair.second.first
                }});
            }
            return std::move(out);
        }
        // TODO: why do things break if this is declared and vals_ is private?
//        friend std::ostream& operator<<(std::ostream& out, table<T> const& table);
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, rr::table<T> const& t) {
        out << "Table{"
            << t.vals_.size()
            << "}"
            << std::endl;
        return out;
    }
};

