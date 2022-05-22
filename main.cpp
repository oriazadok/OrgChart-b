/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

int main() {
    OrgChart organization;
    organization.add_root("SHON")       // Now SHON is the root
        .add_sub("SHON", "ZADOK")         // Now the ZADOK is subordinate to SHON
        .add_root("ORIA")               // Now ORIA is the root
        .add_sub("ORIA", "ROI")         // Now the ROI is subordinate to ORIA
        .add_sub("ORIA", "CAPARA")        // Now the CAPARA is subordinate to ORIA
        .add_sub("ZADOK", "BAR")        // Now the BAR  is subordinate to ZADOK
        .add_sub("ZADOK", "ANTON")       // Now the ANTON is subordinate to ZADOK
        .add_sub("ROI", "ITAMAR")       // Now the ITAMAR is subordinate to ROI
        .add_sub("CAPARA", "SUB");      // Now the SUB is subordinate to CAPARA

  cout << organization << endl; 

    cout << "level order: " << endl;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
        cout << (*it) << " " ;
    } // should print: ORIA ZADOK ROI CAPARA BAR ANTON ITAMAR SUB
    cout << endl;

    cout << "reverse level order: " << endl;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) {
        cout << (*it) << " " ;
    } // should print: BAR ANTON ITAMAR SUB ZADOK ROI CAPARA ORIA
    cout << endl;

    cout << "preorder: " << endl;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        cout << (*it) << " " ;
    }  // should print: ORIA ZADOK BAR ANTON ROI ITAMAR CAPARA SUB
    cout << endl;

    cout << "level order: " << endl;
    for (auto element : organization) { // this should work like level order
        cout << element << " " ;
    } // should print: ORIA ZADOK ROI CAPARA BAR ANTON ITAMAR SUB
    cout << endl;

    cout << "level order sizes: " << endl;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
        cout << it->size() << " " ;
    } // should print: 4 5 3 6 3 5 6 3
    cout << endl;
}