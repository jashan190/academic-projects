#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

// Function definitions with changed names

set<int> uniteSets(const set<int>& setA, const set<int>& setB) {
    set<int> resultSet = setA;
    resultSet.insert(setB.begin(), setB.end());
    return resultSet;
}

set<int> intersectSets(const set<int>& setA, const set<int>& setB) {
    set<int> resultSet;
    for (int element : setA) {
        if (setB.count(element) > 0) {
            resultSet.insert(element);
        }
    }
    return resultSet;
}

set<int> complementSets(const set<int>& universalSet, const set<int>& subset) {
    set<int> resultSet;
    for (int element : universalSet) {
        if (subset.count(element) == 0) {
            resultSet.insert(element);
        }
    }
    return resultSet;
}

set<int> differenceSets(const set<int>& setA, const set<int>& setB) {
    set<int> resultSet = setA;
    for (int element : setB) {
        resultSet.erase(element);
    }
    return resultSet;
}

set<int> symmetricDifferenceSets(const set<int>& setA, const set<int>& setB) {
    set<int> resultSet;
    set<int> unionSet = uniteSets(setA, setB);
    set<int> intersectionSet = intersectSets(setA, setB);
    for (int element : unionSet) {
        if (intersectionSet.count(element) == 0) {
            resultSet.insert(element);
        }
    }
    return resultSet;
}

int main() {
    set<int> set1 = {1, 2, 3, 4, 5};
    set<int> set2 = {3, 4, 7, 8, 9};
    set<int> universalSet = {1, 2, 3, 4, 5, 7, 8, 9};

    int option;
    cout << "Pick a corresponding function 1-5" << endl;
    cout << "1. Union" << endl;
    cout << "2. Intersection" << endl;
    cout << "3. Complement" << endl;
    cout << "4. Difference" << endl;
    cout << "5. Symmetric Difference" << endl;
    cin >> option;

    set<int> resultSet;

    switch (option) {
        case 1:
            resultSet = uniteSets(set1, set2);
            break;
        case 2:
            resultSet = intersectSets(set1, set2);
            break;
        case 3:
            resultSet = complementSets(universalSet, set1);
            break;
        case 4:
            resultSet = differenceSets(set1, set2);
            break;
        case 5:
            resultSet = symmetricDifferenceSets(set1, set2);
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    cout << "Your new set is: ";
    for (int element : resultSet) {
        cout << element << " ";
    }
    cout << endl;

    return 0;
}
 


