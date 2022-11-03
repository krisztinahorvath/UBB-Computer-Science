#include <sstream>
#include <utility>

#include "HospitalDepartment.h"

HospitalDepartment::HospitalDepartment() {

}

HospitalDepartment::~HospitalDepartment() {

}

std::string HospitalDepartment::toString() {
    std::stringstream buffer;
    buffer << this->hospitalName << ", " << this->numberOfDoctors << "\n";
    return buffer.str();
}

NeonatalUnit::NeonatalUnit(std::string name, int nr_doc, int nr_mom, int nr_babies, double grade): HospitalDepartment(std::move(name), nr_doc),
                                                                                                 numberOfMothers(nr_mom), numberOfNewborns(nr_babies), averageGrade(grade){

}

bool NeonatalUnit::isEfficient() {
    if(averageGrade > 8.5 && numberOfNewborns >= numberOfMothers)
        return true;
    return false;
}

std::string NeonatalUnit::toString() {
    std::stringstream buffer;
    std::string ef;
    if(isEfficient())
        ef = "yes";
    else
        ef = "no";

    buffer << "Neonatal Unit, " << hospitalName << ", " << numberOfDoctors << ", " << numberOfNewborns << ", " << averageGrade << ", " << ef << "\n";
    return buffer.str();
}

bool Surgery::isEfficient() {
    if(this->numberOfPatients/this->numberOfDoctors >= 2)
        return true;
    return false;
}

std::string Surgery::toString() {
    std::stringstream buffer;
    std::string ef;
    if(isEfficient())
        ef = "yes";
    else
        ef = "no";
    buffer << "Surgery, " << hospitalName << ", " << numberOfDoctors << ", " << numberOfPatients << ", " << ef << "\n";
    return buffer.str();
}
