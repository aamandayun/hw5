#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;



// Add prototypes for any helper functions here

bool validSchedule(const DailySchedule& sched, const size_t d, const size_t m){
    // vector<Worker_T> validShift(sched[0].size(), 0);
    // for(const auto& day : sched){
    //     for(Worker_T worker : day){
    //         validShift[worker]++;
    //         if(validShift[worker]>m){
    //             return false;
    //         }
    //     }
    // }

    for(const auto& day : sched){
        if(day.size() != d){
            return false;
        }
    }

    return true;
}


//keep track of slot
//make helper return a boolean
bool helper(const AvailabilityMatrix& avail, const size_t d, DailySchedule& sched, size_t day, size_t slot, std::map<Worker_T, int>& canWork){


    bool result = false;
    // cout <<"sched size: " <<sched.size()<<endl;
    if(day == sched.size()){
        return true;
    }

    for(unsigned int id = 0U; id<avail[day].size(); id++){ 
//find(first, last, value)
        auto temp = sched[day].begin()+slot;

        if(temp == std::find(sched[day].begin(), temp, id)){
            //check if worker at id has shifts left AND if they can work that day
            if(canWork[id]>0 && avail[day][id]==true){

                canWork[id]--;
                sched[day][slot] = id;

                //new day
                if(slot==sched[day].size()-1){
                    result = helper(avail, d, sched, day+1, 0U, canWork);
                }else{ //new worker
                    result = helper(avail, d, sched, day, slot+1, canWork);
                }


                if(result == true){
                    return true;
                }


//reset
                sched[day][slot] = INVALID_ID;
                canWork[id]++;
            }
        }

        // if(currentDay.size() < d && currentDay.size() < m){
        //     currentDay.push_back(worker);
        //     helper(avail, d, m, sched, day+1, currentDay);
        //     currentDay.pop_back();
        // }
    }

    // currentDay.clear();
    // cout <<"after clear: "<<currentDay.size()<<endl;
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below


    std::vector<Worker_T> currentDay(dailyNeed, INVALID_ID);
    std::map<Worker_T, int> canWork;

//new day for each in avail
    for(size_t i=0; i<avail.size();i++){
        sched.push_back(currentDay);
    }

    for(int i = 0; i<avail[0].size(); i++){
        canWork.insert(std::make_pair(i, maxShifts));
        cout << canWork[i]<<endl;
    }

    bool result = helper(avail, dailyNeed, sched, 0U, 0U, canWork);
    

    return result;

}

