#include "header.h"
list System;

int main() {
//  cout <<  "\033[48;2;255;100;200m" << endl;
  system("chcp 65001");

  system("cls");
  cout << "\033[97m===================物业维修管理系统===================\033[0m" << endl;
  System.load("data.dat");
  //System.display();
  while (true) {
    cout << "\n\n请选择操作\n\033[091m1.增加记录\n\033[092m2.删除记录\n\033[093m3.修改记录\n\033[094m4.查询预约到期记录\n\033[095m5.查询记录（支持模糊和精确查询）\n\033[096m6.根据楼号统计各幢楼的维修记录数量及总维修收费金额、总维修材料成本金额\n\033[097m7.所有维修记录浏览（以实际维修日期排序显示）\n\033[0m8.!!!保存并退出!!!\033[0m\n";
    int op = INT_MAX;
    do{
      if (op != INT_MAX) cout << "\033[031m错误的指令，请重新输入\033[0m" << endl;
      cin >> op;
      if (cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
      }
    }while(!(op >= 1 && op <= 8));

    cout << "\033[97m------------------------------------------------------------------------------------------------------------------------------------------\033[0m" << endl;

    switch (op) {
    case 1:
      System.add();
      break;
    case 2:
      System.del();
      break;
    case 3:
      System.upgrade();
      break;
    case 4:
      System.findDeadRecord();
      break;
    case 5:
      System.query();
      break;
    case 6:
      System.stats();
      break;
    case 7:
      System.sortByDate();
      System.display();
      break;
    case 8:
      System.save();
      exit(0);
    default:
      cout << "\033[031m错误的指令，请重新输入\033[0m" << endl;
    }
  cout << "\033[97m------------------------------------------------------------------------------------------------------------------------------------------\033[0m" << endl;
  }
}

void printHeadLine(){
  cout << left
       << setw(10) << "序号"
       << setw(20) << "维修住户"
       << setw(19) << "预约日期"
       << setw(19) << "维修日期"
       << setw(34) << "维修内容"
       << setw(19) << "收费金额"
       << setw(19) << "材料成本"
       << setw(13) << "维修人"
       << "备注(是否返修)" << endl;

}