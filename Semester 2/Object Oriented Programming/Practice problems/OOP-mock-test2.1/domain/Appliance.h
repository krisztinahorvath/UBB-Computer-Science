#include <string>
#include <sstream>
#include <utility>

class Appliance
{
protected:
    std::string id;
    double weight{};

public:
    Appliance();
    ~Appliance();
    Appliance(std::string id, double weight): id(std::move(id)), weight(weight){}
    virtual double consumed_electricity() = 0;
    virtual std::string toString();
};

class Refrigerator: public Appliance
{
private:
    std::string electricity_usage_class;
    bool has_freezer;

public:
    Refrigerator(std::string id, double w, std::string el, bool freez): Appliance(std::move(id), w), electricity_usage_class(std::move(el)), has_freezer(freez){}
    ~Refrigerator();
    double consumed_electricity() override ;
    std::string toString() override ;
};

class DishWasher:public Appliance
{
private:
    double washing_cycle_length;
    double consumed_energy_for_one_hour;

public:
    DishWasher(std::string id, double w, double cycle, double cons): Appliance(std::move(id), w),washing_cycle_length(cycle), consumed_energy_for_one_hour(cons) {}
    ~DishWasher();
    double consumed_electricity() override ;
    std::string toString() override ;

};