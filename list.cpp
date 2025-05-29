//
// Created by master on 2025/5/2.
//
#include "header.h"

list::list() {
    head = nullptr;
    tail = nullptr;
    n = 0;
    cnt = 0;
    filename = "None";
}

list::~list(){
  if (head == nullptr) return ;
  Node* temp = head;
  while(head->next != nullptr){
    head = head->next;
    delete temp;
    temp = head;
  }
  delete temp;
}

void list::load(const string& name) {  //文件读取
  fstream file;
  filename = name;
  file.open(name, ios::in);

  if (file.is_open()){
    cout << name << "已打开" << endl;
  }else {
    cout << "无法打开文件，尝试创建新文件..." << endl;
    file.open(name, ios::out);
    if (file.is_open()) {
      std::cout << name << "已成功创建。" << std::endl;
    } else {
      std::cout << "无法创建" << name << "。" << std::endl;
      return ;
    }
    file << 0;
    file.close();
    file.open(name,ios::in);
  }
  int T;
  file >> T;
  string Resident = "None";         //维修住户
  Date ReservationDate;    //预约日期
  Date ActualDate;         //维修日期
  string Content = "None";          //维修内容
  double Charge = 0;           //收费金额
  double Cost = 0;             //材料成本
  string RepairMan = "None";        //维修人
  string Note = "None";             //备注
  while(T--){
    file >> Resident >> ReservationDate >> ActualDate >> Content >> Charge >> Cost >> RepairMan >> Note;
    add(RepairRecord(Resident,ReservationDate,ActualDate,Content,Charge,Cost,RepairMan,Note));
  }
  file.close();

}

void list::findDeadRecord() {
  Node *p = head;
  Date today;
  today.getCurrentDate();
  bool flag = false;
  int count = 1;
  cout << "当前日期:  " << today << endl;
  while(p != nullptr){
    if (p->val.if_dead(today)){
      if (!flag) printHeadLine();
      if (count & 1) cout << "\033[38;2;255;100;200m";
      else cout << "\033[0m";
      cout << left << setw(8) << count;
      p->val.print();
      flag = true;
      count++;
    }
    p = p->next;
  }
  cout << "\033[0m";
  if (!flag) cout << "未找到已到期记录" << endl;
}

void list::save(){
  if (filename == "None"){
    cout << "请先打开一个文件。" << endl;
    return ;
  }

  fstream file;
  file.open(filename,ios::out);
  Node *p = head;
  file << size() << endl;
  while(p){
    file << p->val.getResident() << " " << p->val.getReservationDate() << " "
         << p->val.getActualDate() << " " << p->val.getContent() << " "
         << p->val.getCharge() << " " << p->val.getCost() << " "
         << p->val.getRepairMan() << " " << p->val.getNote() << endl;

    p = p->next;
  }
  file.close();
}

void list::add(){
  string Resident = "None";         //维修住户
  Date ReservationDate;    //预约日期
  Date ActualDate;         //维修日期
  string Content = "None";          //维修内容
  double Charge = 0;           //收费金额
  double Cost = 0;             //材料成本
  string RepairMan = "None";        //维修人
  string Note = "None";             //备注
  cout << "请输入\n住户名 预约日期 维修日期 维修内容 收费金额 材料成本 维修人 备注\n\033[38;2;255;100;200m!!输入114514取消操作!!每项之间用空格隔开(时间格式:(YYYY-MM-DD))\033[0m" << endl;
  cin >> Resident;
  if (Resident == "114514") return ;

  cin >> ReservationDate >> ActualDate >> Content >> Charge >> Cost >> RepairMan >> Note;

  add(RepairRecord(Resident,ReservationDate,ActualDate,Content,Charge,Cost,RepairMan,Note));
  cout << "\033[92m已添加!\033[0m\n\n";
}

void list::add(const RepairRecord &t) {
    n++;
    if (tail == nullptr){
        head = new Node;
        tail = head;
        head->val = t;
        head->next = nullptr;
    }else{
        Node *p = new Node;
        p->val = t;
        p->next = nullptr;
        tail->next = p;
        tail = p;
    }
}

void list::query() {
  cout << "请输入查询内容" << endl;
  string str;cin>>str;
  query(str);
}

void list::query(const string& str) {
  Node *p = head;
  int flag = 0;
  while(p != nullptr){
    if (p->val.find(str)){
      if (flag == 0) printHeadLine();
      flag++;
      if (flag&1)  cout << "\033[38;2;255;100;200m";
      else cout << "\033[0m";
      cout << left << setw(8) << flag;
      p->val.print();

    }
    p = p->next;
  }
  cout << "\033[0m";
  if (flag == 0) cout << "\033[31m未找到!!!\033[0m" << endl;
  else cout << "\033[92m共找到" << flag << "条记录\033[0m" << endl;

}

int count(int num){
  int cnt = 0;
  while(num) {
    cnt++;
    num /= 10;
  }
  return cnt;
}



void list::stats() {
  struct X{
    double first;
    double second; //别问为什么是first和second，问就是最后才看见要统计记录数量
    int sum;
  };
  unordered_map< int, X > a;
  int num, Cnt =1;
  set<int> ans;
  Node *p = head;
  while(p != nullptr){
    num = p->val.getBuildNumber();
    if (!ans.count(num)) ans.insert(num);
    a[num].first += p->val.getCharge();
    a[num].second += p->val.getCost();
    a[num].sum++;
    p = p->next;
  }
  cout << "楼号       总收费金额      总材料成本    记录数量\n";

  for (auto &i : ans){
    if (a[i].first == 0)
      continue;
    if (Cnt++ & 1) cout << "\033[38;2;255;100;200m";
    else cout << "\033[0m";
    cout << i << "号楼" << string(7- count(i),' ') << left << setw(16) << a[i].first << setw(14) << a[i].second  << a[i].sum << endl;
  }
  cout << "\033[0m";
}

void list::display() {
  Node *p = head;
//  cout << "序号\t\t维修住户\t\t预约日期\t\t维修日期\t\t维修内容\t\t\t\t\t\t收费金额\t\t成本金额\t\t维修人\t\t备注(是否返修)" << endl;
  printHeadLine();

  cnt = 1;
  while(p){
    if (cnt & 1) cout << "\033[38;2;255;100;200m";
    else cout << "\033[0m";
    cout << left << setw(8) << cnt;
    cnt++;
    p->val.print();
    p = p->next;
  }
  cout << "\033[0m";
}

void list::del() {
  display();
  int num;
  bool flag = false; //记录输入是否有误
  do{
    if (flag) cout << "\033[31m输入序号有误，请重试\033[0m" << endl;
    flag = true;
    cout << "请输入要删除记录的序号 输入 114514 退出" << endl;
    cin >> num;
    if (num == 114514){
      cout << "已退出删除程序" << endl;
      return ;
    }
  }while(num < 1 || num > n);

  cout << "\033[91m确认删除记录 " << num << " (y/n)\033[0m" << endl;
  char x;cin >> x;
  if (x == 'n'){
    cout << "\033[31m删除失败(用户终止)\033[0m" << endl;
    return ;
  }

  Node *p = head;
  cnt = 2;
  if (num == 1){
    p = head->next;
    delete head;
    head = p;
  }else if (num == n){
    while (p->next != tail) p = p->next;
    delete tail;
    tail = p;
    tail->next = nullptr;
  }else {
    while(cnt != num){
      cnt++;
      p = p->next;
    }
    Node *q = p->next;
    p->next = q->next;
    delete q;
  }
  n--;
  cout << "\033[92m已删除!\n\n\033[0m";
}

void list::upgrade() {
  display();
  int num;
  bool flag = false;
  do{
    if (flag) cout << "\033[31m输入序号有误，请重试\033[0m" << endl;
    flag = true;
    cout << "请输入要修改记录的序号 输入 114514 退出" << endl;
    cin >> num;
    if (num == 114514){
      cout << "已退出修改程序" << endl;
      return ;
    }
  }while(num < 1 || num > n);

  cnt = 1;
  Node *p = head;
  while(cnt != num){
    p = p->next;
    cnt++;
  }
  p->val.upgrade();
}

Node* list::merge(Node *left, Node *right) { //合并两个链表
  if (left == nullptr) return right;
  if (right == nullptr) return left;
  Node* headptr = nullptr;
  Node* temp = nullptr;
  while(left != nullptr && right != nullptr){
    if (left->val.getActualDate() < right->val.getActualDate()){
      if (temp == nullptr){
        headptr = left;
        temp = headptr;
        left = left->next;
        continue;
      }
      temp->next = left;
      temp = left;
      left = left->next;
    }else{
      if (temp == nullptr){
        headptr = right;
        temp = headptr;
        right = right->next;
        continue;
      }
      temp->next = right;
      temp = right;
      right = right->next;
    }
  }

  if (temp != nullptr){ //clion提示temp可能为nullptr，但这是不可能的
    if (left == nullptr)
      temp->next = right;
    else
      temp->next = left;
  }else{
    headptr = left ? left : right;
  }

  return headptr;
}

Node* list::sortByDate(Node*headptr) { //归并排序
  if (headptr == nullptr || headptr->next == nullptr) return headptr;
  Node* slow = headptr;
  Node* fast = headptr->next;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  Node* right = slow->next;
  slow->next = nullptr;

  Node* left_sorted = sortByDate(headptr);
  Node* right_sorted = sortByDate(right);

  return merge(left_sorted, right_sorted);
}

void list::sortByDate() {
  head = sortByDate(head);

  Node* temp = head; //更新tail节点
  while(temp->next != nullptr) temp = temp->next;
  tail = temp;
}