//
// Created by master on 2025/5/7.
//

#ifndef REPAIRSYSTEM_REPAIRRECORD_H
#define REPAIRSYSTEM_REPAIRRECORD_H
#include "header.h"

class RepairRecord{
private:
  string Resident;         //维修住户
  Date ReservationDate;    //预约日期
  Date ActualDate;         //维修日期
  string Content;          //维修内容
  double Charge;           //收费金额
  double Cost;             //材料成本
  string RepairMan;        //维修人
  string Note;             //备注(是否返修)
  string date;
public:
  RepairRecord();
  [[maybe_unused]] RepairRecord(const RepairRecord&);
  RepairRecord(const string& rt, const Date& re, const Date& ae,const string& ct, const double& ce, const double& cst, const string& rn, const string& nt):
                             Resident(rt), ReservationDate(re), ActualDate(ae), Content(ct), Charge(ce), Cost(cst), RepairMan(rn), Note(nt){ date = "None"; };
  void print();
  void upgrade();
  Date getActualDate(){ return ActualDate; }
  string getResident(){ return Resident; }
  Date getReservationDate(){ return ReservationDate; }
  string getContent(){ return Content;}
  double getCharge() const{ return Charge;}
  double getCost() const{ return Cost;}
  string getRepairMan(){ return RepairMan;}
  string getNote(){ return Note;}
  int getBuildNumber();
  bool if_dead(const Date&);
  bool find(const string&);
  friend ostream& operator<<(ostream&,const RepairRecord&);
};


#endif // REPAIRSYSTEM_REPAIRRECORD_H
