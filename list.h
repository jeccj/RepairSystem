//
// Created by master on 2025/5/7.
//

#ifndef REPAIRSYSTEM_LIST_H
#define REPAIRSYSTEM_LIST_H
#include "header.h"

struct Node{
  RepairRecord val;
  Node *next;
};

class list{
private:
  Node *head;
  Node *tail;
  int n;
  int cnt;
  string filename;
public:
  list();
  ~list();
  void add();
  void add(const RepairRecord& );
  void del();
  void upgrade();
  void display();
  void findDeadRecord();
  void stats();
  void query();
  void query(const string& str);
  void sortByDate();
  Node* sortByDate(Node*);
  static Node* merge(Node*, Node*);
  void load(const string&);
  void save();
  int size() const{ return n; }
};


#endif // REPAIRSYSTEM_LIST_H
