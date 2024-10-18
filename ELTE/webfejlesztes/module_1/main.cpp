struct h1l {
  int key;
  h1l* next;
};

void f(h1l* head){
  auto pe = head;
  auto p = head->next;

  while(p != nullptr && p->key >= 0){
    pe =p;
    p = p->next;
  }

  auto pu = pe;

  while(p!=nullptr){
    if(p->key < 0){
      pe = p;
      p = p->next;
    }
    else {
    pe->next = p->next;
      p->next = pu->next;
      pu->next = p;
      p = pe->next;
      pu = pu->next;
  }
  }
}
