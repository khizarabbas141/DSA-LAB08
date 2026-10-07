#include <iostream>
using namespace std;
struct song{
    int id;
    string name;
    int duration; 
    song* next;
    song* prev;
};
class PlayList{
    private:
        song* head;
        song* tail;
        song * newSong;

    public:
        PlayList(){
            head = nullptr;
            tail = nullptr;
            newSong =  nullptr;
        }
        
        void addSong(int id,const string& name, int duration) {
            newSong = new song;
            newSong->id = id;
            newSong->name = name;
            newSong->duration = duration;
            newSong->next = nullptr;
            newSong->prev =  nullptr;

            if (head == nullptr) {
                head = newSong;
                tail =  newSong;
            } else {
                tail->next = newSong;
                newSong->prev = tail;
                tail =  newSong;
            }
        }
        void deleteSong(int id) {
            song* current = head;
            while (current != nullptr) {
                if (current->id == id) {
                    if (current->prev != nullptr) {
                        current->prev->next =  current->next;
                    } else {
                        head = current->next;
                    }
                    if (current->next != nullptr) {
                        current->next->prev = current->prev;
                    } else {
                        tail  = current->prev; 
                    }
                    delete current;
                    return;
                }
                current =  current->next;
            }
        }
        void displaySongs() {
            song* current = head;
            while (current != nullptr) {
                cout << "ID: " << current->id << ", Name: " << current->name << ", Duration: " << current->duration << " seconds" << endl;
                current = current->next;
            }
        }
        void displaySongsReverse() {
            song* current = tail;
            while (current != nullptr) {
                cout << "ID: " << current->id << ", Name: " << current->name << ", Duration: " << current->duration << " seconds" << endl;
                current = current->prev;
            }
        }
        void searchSong(int id) {
            song* current = head;
            while (current != nullptr) {
                if (current->id == id) {
                    cout << "Found Song! ID: " << current->id << ", Name: " << current->name << ", Duration: " << current->duration << " seconds" << endl;
                    return;
                }
                current = current->next;
            }
            cout << "Song with ID " << id << " not found!" << endl;
        }
        void playnext() {
            if (head == nullptr) {
                cout << "Playlist is empty." << endl;
                return;
            }
            static song* current = head;
            cout << "Playing next song! ID: " << current->id << ", Name: " << current->name << ", Duration: " << current->duration << " seconds" << endl;
            current = (current->next != nullptr) ? current->next : head; 
        }
        void playprev() {
            if (tail == nullptr) {
                cout << "Playlist is empty!" << endl;
                return;
            }
            static song* current = tail;
            cout << "Playing previous song! ID: " << current->id << ", Name: " << current->name << ", Duration: " << current->duration << " seconds" << endl;
            current = (current->prev != nullptr) ? current->prev : tail; 
        }
        void reversePlaylist() {
            song * current = head;
            song* temp = nullptr;

            while (current != nullptr) {
                temp = current->prev;
                current->prev = current->next;
                current->next =  temp;

                current = current->prev;
            }
            if (temp != nullptr) {
                head = temp->prev; 
            }
        }


};
int main(){
    PlayList playlist;
    playlist.addSong(1, "blue", 210);
    playlist.addSong(2, "gangnum style", 180);
    playlist.addSong(3, "intersteller", 240);
    playlist.addSong(4, "pen", 200);
    cout << "Displaying songs in order:" << endl;
    playlist.displaySongs();
    cout << "\nDisplaying songs in reverse order:" << endl;
    playlist.displaySongsReverse();
    cout << "\nSearching for song with ID 2:" << endl;
    playlist.searchSong(2);
    cout << "\nPlaying next song:" << endl;
    playlist.playnext();
    cout << "\nPlaying previous song:" << endl;
    playlist.playprev();
    cout << "\nReversing the playlist:" << endl;
    playlist.reversePlaylist();
    cout << "\nDisplaying songs in order after reversing:" << endl;
    playlist.displaySongs();
    playlist.deleteSong(3);
    cout << "\nDisplaying songs after deleting song with ID 3:" << endl;
    playlist.displaySongs();
}