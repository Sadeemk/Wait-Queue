// Programmer: Sadeem Khan
// Programmer's ID: 1549921

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <ctime>
#include <cmath>
#include <cstdlib>

#include "DynamicArray.h"
#include "Queue.h"

struct Customer
{
  char idTag;
  int arrivalTime;
  int serviceEndTime;
};

int getRandomNumberOfArrivals(double);
char assignID(char&);

int main()
{
  // Identification
  cout << "Programmer: Sadeem Khan\n";
  cout << "Programmer's ID: 1549921\n";
  cout << "File: " << __FILE__ << endl;

  srand(time(0)); rand(); // requires cstdlib and ctime

  int numberOfServers = 0;
  double averageArrivalRate = 0.0;
  int maxLengthWaitQueue = 0;
  int minimumServiceTime = 0;
  int maximumServiceTime = 0;
  int clockTimeStop = 0;

  char firstId = 'A';

  ifstream fin;
  fin.open("simulation.txt");
  string a;
  getline(fin, a);
  numberOfServers = atoi(a.c_str());

  string b;
  getline(fin, b);
  averageArrivalRate = atoi(b.c_str());

  string c;
  getline(fin, c);
  maxLengthWaitQueue = atoi(c.c_str());

  string d;
  getline(fin, d);
  minimumServiceTime = atoi(d.c_str());

  string e;
  getline(fin, e);
  maximumServiceTime = atoi(e.c_str());

  string f;
  getline(fin, f);
  clockTimeStop = atoi(f.c_str());

  cout << "number of servers: " << numberOfServers << endl;
  cout << "customer arrival rate: " << averageArrivalRate << " per minute, for " << clockTimeStop << " minutes" << endl;
  cout << "maximum queue length: " << maxLengthWaitQueue << endl;
  cout << "minimum service time: " << minimumServiceTime << " minutes" << endl;
  cout << "maximum service time: " << maximumServiceTime << " minutes" << endl;

  Queue<Customer> waitQueue;
  DynamicArray<Customer> nowServing;
  DynamicArray<bool> serverFreeOrNot;

  // the clock time loop
  for (int time = 0;; time++) // the clock time
  {
    // handle all services scheduled to complete at this clock time
    for (int i = 0; i < numberOfServers; i++) // for each server
      if (serverFreeOrNot[i]) // if the server is busy
        if (nowServing[i].serviceEndTime == time) // if the service end time of the customer that it's now serving equals the clock time
          serverFreeOrNot[i] = false; // set server to idle, false means idle.

    // handle new arrivals -- can be turned away if wait queue is at maximum length!
    if (time < clockTimeStop) // if clock time is less than the time at which new arrivals stop
    {
      averageArrivalRate = getRandomNumberOfArrivals(averageArrivalRate); // get #of of arrivals from the "Poisson process"
      for (int i = 0; i < averageArrivalRate; i++) // for each new arrival
      {
        if (waitQueue.size() < maxLengthWaitQueue) // if the wait queue is not full
        {
          Customer a; // new customer object
          a.arrivalTime = time; // set its arrival time equal to current clock time
          a.idTag = assignID(firstId);
          waitQueue.push(a); // push new customer into the wait queue
        }
      }
    }

    // for idle servers, move customer from wait queue and begin service
    for(int i = 0; i < numberOfServers; i++) // for each server
    {
      if(!serverFreeOrNot[i] && !waitQueue.empty()) // if server is idle and wait queue is not empty
      {
        nowServing[i] = waitQueue.front(); // copy top customer from the wait queue to the idle server
        waitQueue.pop(); // remove that customer from wait queue
        nowServing[i].serviceEndTime = time + (minimumServiceTime + rand() % ((maximumServiceTime - minimumServiceTime) + 1)); // set service endtime to current clock time PLUS "random service interval"
        serverFreeOrNot[i] = true; // mark that server as busy
      }
    }

    //output the summary
    cout <<"\nTime: " << time << endl; //output the current time
    cout << "---------------------------" << endl; //output a visual representation of the servers and the wait queue
    cout << "server now serving wait queue" << endl;
    cout << "------ ----------- ----------" << endl;
    for(int i = 0; i < numberOfServers; i++)
    {
      char output = ' ';
      if(serverFreeOrNot[i]) output = nowServing[i].idTag; //servers[i].cust.ID;
      cout.width(3);
      cout << i;
      cout.width(10);
      cout << output;
      if(i == 0)
      {
        Queue<Customer> temp = waitQueue;
        cout.width(10);
        while(!temp.empty())
        {
          cout << temp.front().idTag;
          temp.pop();
        }
      }
      cout << endl;   
    }

    // How many idle servers there are
    int idleServers = 0;
    for(int i = 0; i < numberOfServers; i++)
      if (!serverFreeOrNot[i]) 
        idleServers++;
    
    // since there are only 4 servers, if the number of idle servers = 4 and the time is done, the simulation is over
    if (idleServers == numberOfServers && time >= clockTimeStop)
    {
      cout << "Done!" << endl;
      break;
    }

    cout << '\n' << "Press ENTER to continue...";
    cin.get();
  }
}

char assignID(char& firstId)
{ 
  // if the id is z
  if(firstId == 'Z')
  { 
    // assign the next id as A and so on
    firstId = 'A';
    return 'Z';
  }
  return firstId++;
}

int getRandomNumberOfArrivals(double averageArrivalRate)
{
  int arrivals = 0;
  double probOfnArrivals = exp(-averageArrivalRate);
  for (double randomValue = (double)rand() / RAND_MAX; 
    (randomValue -= probOfnArrivals) > 0.0; 
    probOfnArrivals *= averageArrivalRate / static_cast<double>(++arrivals));
  return arrivals;
}