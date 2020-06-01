#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
  friend ostream &operator<<(ostream &os, ListNode *node)
  {
    while (node != nullptr)
    {
      os << node->val << ' ';
      node = node->next;
    }
    os << endl;
    return os;
  }
};

auto compare = [](const ListNode *a, const ListNode *b) {
  if (!a || !b)
  {
    return false;
  }
  return a->val > b->val;
};

class Solution
{
public:
  vector<ListNode *> sanitize(vector<ListNode *> &lists)
  {
    lists.erase(remove_if(lists.begin(), lists.end(), [](ListNode *a) {
                  return a == nullptr;
                }),
                lists.end());
    return lists;
  }
  
  ListNode *mergeKLists(vector<ListNode *> &lists)
  {
    ListNode *output = nullptr, *last = nullptr;
    lists = sanitize(lists);
    make_heap(lists.begin(), lists.end(), compare);
    while (!lists.empty())
    {
      cout << "next" << endl;
      for_each(lists.begin(), lists.end(), [](ListNode *each) {
        cout << each;
      });
      pop_heap(lists.begin(), lists.end(), compare);
      auto &opList = lists.back();
      if (!opList)
      {
        lists.pop_back();
        continue;
      }
      auto curr = opList;
      opList = opList->next;

      curr->next = nullptr;
      if (output == nullptr)
      {
        output = curr;
        last = curr;
      }
      else
      {
        last->next = curr;
        last = curr;
      }
      if (opList == nullptr)
      {
        lists.pop_back();
        continue;
      }
      make_heap(lists.begin(), lists.end(), compare);
    }
    cout << " output " << output;
    return output;
  }
};

struct deletePtr
{
  template <typename P>
  void operator()(P p)
  {
    while (p != nullptr)
    {
      auto &t = p->next;
      delete p;
      p = t;
    }
  }
};

ListNode *reverseList(ListNode *lst)
{
  if (lst == nullptr)
  {
    return nullptr;
  }
  ListNode *head = lst;
  ListNode *curr = head->next;
  head->next = nullptr;
  ListNode *moving = head;
  while (curr != nullptr)
  {
    ListNode *temp = curr->next;
    curr->next = moving;
    moving = curr;
    curr = temp;
  }
  return moving;
}

int main()
{
  int tc;
  stringstream ss;
  string line;
  ifstream fin("k-sorted-lists.txt");

  getline(fin, line);
  ss << line;
  ss >> tc;
  ss.clear();

  for (int i = 0; i < tc; ++i)
  {
    int countLists;
    getline(fin, line);
    ss << line;
    ss >> countLists;
    ss.clear();
    vector<ListNode *> lists(countLists);
    for (int j = 0; j < countLists; ++j)
    {
      getline(fin, line);
      ss << line;
      if (line.size() == 0)
      {
        lists[j] = nullptr;
        continue;
      }
      int k = 0;
      int num;
      while (ss >> num)
      {
        cout << "num" << num << " ";
        if (k == 0)
        {
          ListNode *first = new ListNode(num);
          lists[j] = first;
        }
        else
        {
          ListNode *next = new ListNode(num, lists[j]);
          lists[j] = next;
        }
        k++;
      }
      ss.clear();
      k = 0;
    }
    for_each(lists.begin(), lists.end(), [](ListNode *a) {
      cout << a;
    });
    transform(lists.begin(), lists.end(), lists.begin(), reverseList);
    Solution().mergeKLists(lists);
    for_each(lists.begin(), lists.end(), deletePtr());
    lists.clear();
  }
}
