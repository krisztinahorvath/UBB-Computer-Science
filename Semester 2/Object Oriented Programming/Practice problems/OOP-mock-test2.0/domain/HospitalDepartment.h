#pragma once
#include <string>
#include <utility>

class HospitalDepartment {
protected:
    std::string hospitalName;
    int numberOfDoctors;

public:
    HospitalDepartment();
    HospitalDepartment(std::string name, int nr): hospitalName(std::move(name)), numberOfDoctors(nr) {}
    ~HospitalDepartment();
    virtual bool isEfficient() = 0 ;
    virtual std::string toString();
    std::string get_name() {return this->hospitalName;}

};

class NeonatalUnit: public HospitalDepartment{
private:
    int numberOfMothers;
    int numberOfNewborns;
public:
    double averageGrade;

    NeonatalUnit(std::string name, int nr_doc, int nr_mom, int nr_babies, double grade);
    bool isEfficient() override;
    std::string toString() override;
};

class Surgery: public HospitalDepartment{
private:
    int numberOfPatients;

public:
    Surgery(std::string name, int nr_doc, int nr_pat): HospitalDepartment(std::move(name), nr_doc), numberOfPatients(nr_pat){}
    bool isEfficient() override;
    std::string toString() override;
};


