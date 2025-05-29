//
// Created by master on 2025/5/1.
//
#include "header.h"

RepairRecord::RepairRecord() {
    Resident = "None";
    ReservationDate = Date();
    ActualDate = Date();
    Content = "None";
    Charge = 0;
    Cost = 0;
    RepairMan = "None";
    Note = "None";
    date = "None";
}

[[maybe_unused]] RepairRecord::RepairRecord(const RepairRecord& record){ //似乎并没有用
    Resident = record.Resident;
    ReservationDate = record.ReservationDate;
    ActualDate = record.ActualDate;
    Content = record.Content;
    Charge = record.Charge;
    Cost = record.Cost;
    RepairMan = record.RepairMan;
    Note = record.Note;
    date = "None";
}

/*
string Resident;         //维修住户
Date ReservationDate;    //预约日期
Date ActualDate;         //维修日期
string Content;          //维修内容
double Charge;           //收费金额
double Cost;             //材料成本
string RepairMan;        //维修人
string Note;             //备注(是否返修)
*/
int count(const string& utf8Str) {
  int count = 0,cnt = 0;
  for (size_t i = 0; i < utf8Str.size();) {
    auto byte = static_cast<unsigned char>(utf8Str[i]);
    int charSize;
    // 判断UTF-8字符的字节长度
    if ((byte & 0x80) == 0) {
      charSize = 1; // ASCII字符
    } else if ((byte & 0xE0) == 0xC0) {
      charSize = 2;
    } else if ((byte & 0xF0) == 0xE0) {
      charSize = 3;
    } else if ((byte & 0xF8) == 0xF0) {
      charSize = 4;
    } else {
      // 无效的UTF-8起始字节，跳过
      i++;
      continue;
    }
    // 多字节字符通常为全角字符（如中文、日文、韩文等）
    if (charSize > 1) {
      count++;
    }else cnt++;
    i += charSize;
  }
  return 2*count+cnt;
}

bool RepairRecord::if_dead(const Date &today) {
    return today > ActualDate;
}

bool RepairRecord::find(const std::string& str) {
  if (Content.find(str) != string::npos) return true;
  if (Resident.find(str) != string::npos) return true;
  if (ReservationDate.toString().find(str) != string::npos) return true;
  if (ActualDate.toString().find(str) != string::npos) return true;
  if (to_string(Charge).find(str) != string::npos) return true;
  if (to_string(Cost).find(str) != string::npos) return true;
  if (RepairMan.find(str) != string::npos) return true;
  if (Note.find(str) != string::npos) return true;
  return false;
}

void RepairRecord::print(){ // 讨厌调格式，巨烦
  cout << left
       << Resident << string(16 - count(Resident),' ')
       << setw(15) << ReservationDate.toString()
       << setw(15) << ActualDate.toString()
       << Content << string(max(0,30 - count(Content)),' ')
       << setw(15) << fixed << setprecision(2) << Charge  // 金额显示两位小数
       << setw(15) << fixed << setprecision(2) << Cost
       << RepairMan << string(max(0,10 - count(RepairMan)),' ')
       << Note << endl;
}

/*ostream& operator<<(ostream& os,const RepairRecord& record){
    os << "维修住户:\t" << record.Resident << endl
       << "预约日期:\t" << record.ReservationDate << endl
       << "维修日期:\t" << record.ActualDate << endl
       << "维修内容:\t" << record.Content << endl
       << "收费金额:\t" << record.Charge << endl
       << "材料成本:\t" << record.Cost << endl
       << "维修人:\t"  << record.RepairMan << endl
       << "备注:\t"    << record.Note;
    return os;
} */

//（）
//胡胡
//aaa

int RepairRecord::getBuildNumber() {
  int num = 0;
  for (char x : Resident){
    if (x >= '0' && x <= '9'){
      num = num * 10 + (x - '0');
    }else break;
  }
  return num;
}

void RepairRecord::upgrade() {
    while(true){
        printHeadLine();
        cout << "\033[38;2;255;100;200m";
        cout << left << setw(8) << 1;
        print();
        cout << "\033[0m";
        cout<<"请输入要修改的内容"<<endl
            << "1.维修住户" <<endl
            << "2.预约日期" <<endl
            << "3.维修日期" <<endl
            << "4.维修内容" <<endl
            << "5.收费金额" <<endl
            << "6.材料成本" <<endl
            << "7.维修人"  <<endl
            << "8.备注"    <<endl
            << "9.退出!!!"    <<endl;
        int op;
        cin>>op;
        switch (op) {
            case 1:{
                cout<<"维修住户: \033[38;2;255;100;200m"<< Resident << "\033[0m -> \033[38;2;255;100;200m";
                cin >> Resident;
                break;
            }
            case 2:{
                cout<<"预约日期(示例:2025-5-1): \033[38;2;255;100;200m"<< ReservationDate << "\033[0m -> \033[38;2;255;100;200m";
                cin >> ReservationDate;
                break;
            }
            case 3:{
                cout<<"维修日期(示例:2025-5-1): \033[38;2;255;100;200m"<< ActualDate << "\033[0m -> \033[38;2;255;100;200m";
                cin >> ActualDate;
                break;
            }
            case 4:{
                cout<<"维修内容: \033[38;2;255;100;200m"<< Content << "\033[0m -> \033[38;2;255;100;200m";
                cin >> Content;
                break;
            }
            case 5:{
                cout<<"收费金额: \033[38;2;255;100;200m"<< Charge << "\033[0m -> \033[38;2;255;100;200m";
                cin >> Charge;
                break;
            }
            case 6:{
                cout<<"材料成本: \033[38;2;255;100;200m"<< Cost << "\033[0m -> \033[38;2;255;100;200m";
                cin >> Cost;
                break;
            }
            case 7:{
                cout<<"维修人: \033[38;2;255;100;200m"<< RepairMan << "\033[0m -> \033[38;2;255;100;200m";
                cin >> RepairMan;
                break;
            }
            case 8:{
                cout<<"备注: \033[38;2;255;100;200m"<< Note << "\033[0m -> \033[38;2;255;100;200m";
                cin >> Note;
                break;
            }
            case 9: return ;
            default: cout << "输入失败请重试" << endl;
        }
        cout << "\033[92m已修改!\033[0m" << endl;
    }

}
