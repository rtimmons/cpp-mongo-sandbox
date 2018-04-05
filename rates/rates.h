#include <utility>
#include <string>
#include <map>

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

    template <class T>
    class table {
    public:
        template <typename...Args>
        table(Args&&...args)
        : vals(std::forward<Args>(args)...) {}

        template <typename...Args>
        void insert(Args&&...args) {
            this->vals.insert(std::forward<Args>(args)...);
        }
    private:
        std::multimap<unit,equiv<T>> vals;
    };

};

