#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Place {
public:
    string name;
    string title;
    string description;
    bool newPlace = 1;
    string inventory[128];
    string exits[8];
    Place() {
        for (int i = 0; i < 128; i++)
            inventory[i] = "~";
        for (int i = 0; i < 8; i++)
            exits[i] = "~";
    }

};
class Item {
public:
    string name;
    string title;
};

string getInput() {
    string input;
    getline(cin, input);
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    for_each(input.begin(), input.end(), [](char& c) { c = ::tolower(c); });
    return input;
}

int main()
{   

    // INVENTORY
    const int inventorySize = 8;
    const int numItems = 128;
    const int numPlaces = 64;
    string inventory[inventorySize];
    for (int i = 0; i < inventorySize; i++)
        inventory[i] = "~";
    sort(begin(inventory), end(inventory));



    // PLACES
    Place place[numItems];

    // Alley
    place[0].name = "alley";
    place[0].title = "Dark Alley";
    place[0].description = "You are in an alley. There is a street on the left and a way to the port on the right.";
    place[0].exits[0] = "port";
    place[0].exits[1] = "street";
    place[0].inventory[0] = "paper";
    place[0].inventory[1] = "axe";
    place[0].inventory[2] = "button";

    // Port
    place[1].name = "port";
    place[1].title = "Port";
    place[1].description = "You are in the port. The way leads to a dark alley.";
    place[1].exits[0] = "alley";

    // Street
    place[2].name = "street";
    place[2].title = "Street";
    place[2].description = "You are on a busy street. There is a dark alley on the right.";
    place[2].exits[0] = "alley";

    for (int i = 0; i < numPlaces; i++)
        sort(begin(place[i].inventory), end(place[i].inventory));



    // ITEMS
    Item item[numPlaces];

    // Paper
    item[0].name = "paper";
    item[0].title = "A Suspicious Paper";

    // Axe
    item[1].name = "axe";
    item[1].title = "The Axe Of War";
    
    // Button
    item[2].name = "button";
    item[2].title = "A Gray Button";



    // INITIALIZATION
    string input;
    int in = 0;



    // TUTORIAL
    cout << "Do you want an introduction? ";
    input = getInput();
    cout << endl;
    while (!(input.find("y") != string::npos) && !(input.find("n") != string::npos)) {
        
    }
    if (input.find("y") != string::npos) {
        cout << "Here is your tutorial: N/A\n";
    }
    else if (input.find("n") != string::npos) {
    }



    // GAME
    while (1) {
        // Place Description
        cout << endl << place[in].title << endl;
        if (place[in].newPlace == 1) {
            cout << place[in].description << endl;
            place[in].newPlace = 0;
        }
        // Items
        if (place[in].inventory[0] != "~") {
            cout << "\nYou can see:\n";
            for (int i = 0; i < 64; i++) {
                if (place[in].inventory[i] != "~") {
                    for (int j = 0; j < 64; j++) {
                        if (place[in].inventory[i] == item[j].name) {
                            cout << item[j].title << endl;
                            break;
                        }
                    }
                }
                else
                    break;
            }
        }
        // Commands
        input = getInput();
        cout << endl;
        // Look
        if (input.find("look") != string::npos) {
            place[in].newPlace = 1;
        }
        // Inventory
        else if (input.find("inv") != string::npos) {
            if (inventory[0] != "~") {
                cout << "You are carrying:\n";
                for (int i = 0; i < inventorySize; i++) {
                    if (inventory[i] != "~") {
                        for (int j = 0; j < inventorySize; j++) {
                            if (inventory[i] == item[j].name) {
                                cout << item[j].title << endl;
                                break;
                            }
                        }
                    }
                    else
                        break;
                }
                cout << endl;
            }
            else {
                cout << "There is nothing in your inventory\n";
            }
            cout << endl;
        }
        // Move
        else if (input.find("travelto") != string::npos || input.find("goto") != string::npos || input.find("moveto") != string::npos || input.find("moveinto") != string::npos || input.find("access") != string::npos) {
            bool errorMove = 0;
            for (int i = 0; i < 64; i++) {
                if (input.find(place[i].name) != string::npos) {
                    errorMove = 1;
                    for (int j = 0; j < 8; j++) {
                        if (place[in].exits[j] == place[i].name) {
                            in = i;
                            errorMove = 0;
                            break;
                        }
                    }
                    if (errorMove == 0)
                        break;
                }
            }
            if (errorMove == 1)
                cout << "You can't move to this place\n";
        }
        // Take
        else if (input.find("take") != string::npos || input.find("get") != string::npos || input.find("pick") != string::npos || input.find("grab") != string::npos || input.find("get") != string::npos) {
            bool errorTake = 1, errorTakeFull = 1;
            for (int i = 0; i < numItems; i++) {
                if (input.find(item[i].name) != string::npos) {
                    for (int j = 0; j < 64; j++) {
                        if (item[i].name == place[in].inventory[j]) {
                            errorTake = 0;
                            for (int t = 0; t < inventorySize; t++) {
                                if (inventory[t] == "~") {
                                    errorTakeFull = 0;
                                    inventory[t] = item[i].name;
                                    sort(begin(inventory), end(inventory));
                                    place[in].inventory[j] = "~";
                                    sort(begin(place[in].inventory), end(place[in].inventory));
                                    cout << "Got it!\n";
                                    break;
                                }
                            }
                        }
                    }
                }
                if (errorTake == 0 && errorTakeFull == 0)
                    break;
            }
            if (errorTake == 1)
                cout << "There is no such item here\n";
            else if (errorTakeFull == 1)
                cout << "Your inventory is full\n";
        }
        // Drop
        else if (input.find("drop") != string::npos) {
            bool errorDrop = 1;
            for (int i = 0; i < numItems; i++) {
                if (input.find(item[i].name) != string::npos) {
                    for (int j = 0; j < inventorySize; j++) {
                        if (item[i].name == inventory[j]) {
                            errorDrop = 0;
                            for (int t = 0; t < 128; t++) {
                                if (place[in].inventory[t] == "~") {
                                    place[in].inventory[t] = item[i].name;
                                    sort(begin(place[in].inventory), end(place[in].inventory));
                                    inventory[j] = "~";
                                    sort(begin(inventory), end(inventory));
                                    cout << "Got it!\n";
                                    break;
                                }
                            }
                        }
                    }
                }
                if (errorDrop == 0)
                    break;
            }
            if (errorDrop == 1)
                cout << "You dont have this item\n";
        }
        // Error
        else {
            cout << "I don't recognize this sentence\n";
        }
    }
}