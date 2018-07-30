// Programmer: Sadeem Khan
// Programmer's ID: 1549921

#include <iostream>
using namespace std;

#include<cassert>

#include "Queue.h"
#include "Queue.h"

int main()
{
  // Identification
  cout << "Programmer: Sadeem Khan\n";
  cout << "Programmer's ID: 1549921\n";
  cout << "File: " << __FILE__ << endl;

  // Test using ints
  Queue<int> a;
  assert(a.size() == 0);

  cout << "\nTesting push, pop, front, back, empty and clear\n";
  a.push(3131);
  a.push(2121);
  cout << "EXPECTED: 3131\n";
  cout << "ACTUAL: " << a.front() << endl;
  cout << "Expected: 2121" << endl;
  cout << "Actual result: " << a.back() << endl;
  a.pop();
  cout << "Expected: 1" << endl;
  cout << "Actual result: " << a.size() << endl;
  a.clear();
  cout << "Expected: 1" << endl;
  cout << "Actual result: " << a.empty() << endl;

  // Const object test
  cout << "\nConst object test" << endl;
  const Queue<int> c;
  assert(c.size() == 0);
  assert(c.empty());

  a.push(3200);
  a.push(4200);
  // object copy test
  cout << "\nObject copy test\n";
  Queue<int> d = a; // making a copy
  assert(a.size() == d.size());
  for (int i = 0; i < a.size(); i++)
  {
    assert(a.front() == d.front());
    a.pop();
    d.pop();
  }

  a.push(5200);
  a.push(6200);
  // object assignment test
  cout << "\nObject assignment test\n";
  Queue<int> e; e = a;
  assert(a.size() == e.size());
  for (int i = 0; i < 10; i++) 
  {
    assert(a.size() == e.size());
    a.pop();
    e.pop();
  }
}