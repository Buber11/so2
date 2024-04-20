#include <GLFW/glfw3.h>
#include <iostream>
#include<thread>
#include<vector>
#include <algorithm>
#include<random>
#include</home/jakub/laby/Rectangel.h>
#include</home/jakub/laby/Color.h>

using namespace std;

bool stopFlag = false;

std::vector<Rectangel*> Rectangel::objects;

Rectangel::Rectangel(float theX, float theY, float theSpeed, Color theColor) : x(theX), y(theY), speed(theSpeed), color(theColor) {}

float Rectangel::random_speed(float min_speed, float max_speed){
    // Inicjalizacja generatora liczb losowych
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Określenie zakresu losowania prędkości
    std::uniform_real_distribution<float> dist(min_speed, max_speed);
    
    // Wylosowanie wartości prędkości z podanego zakresu
    return dist(gen);
}

void Rectangel::draw() {
    glColor3f(color.red, color.green, color.blue);

    glBegin(GL_QUADS); // Rozpoczęcie rysowania kwadratu
    // Określenie współrzędnych wierzchołków kwadratu
    // Lewy dolny róg
    glVertex2f(x - width/2, y - height/2); 

    // Prawy dolny róg
    glVertex2f(x + width/2, y - height/2); 

    // Prawy górny róg
    glVertex2f(x + width/2, y + height/2); 

    // Lewy górny róg
    glVertex2f(x - width/2, y + height/2); 
    glEnd(); // Zakończenie rysowania kwadratu
}

void Rectangel::moveRight() {
    for (auto& next : Rectangel::objects) {
        if (this == next) continue;
        float diff_x = next->x - this->x;
        float diff_y = next->y - this->y;
        if (diff_x >= 0.0f && diff_x <= 0.1f && diff_y >=-0.05f && diff_y <=0.05f) {
            return;
        }
    }
    x += speed; // Przesunięcie w prawo
}

void Rectangel::moveLeft() {
    for (auto& next : Rectangel::objects) {
        if (this == next) continue;
        float diff_x = next->x - this->x;
        float diff_y = next->y - this->y;
        if (diff_x <=  0.0f && diff_x >= -0.1f && diff_y <= 0.05f && diff_y >= -0.05f) {
            return;
        }
    }
    x -= speed; // Przesunięcie w lewo
}

void Rectangel::moveUp() {
    for (auto& next : Rectangel::objects) {
        if (this == next) continue;
        float diff_x = next->x - this->x;
        float diff_y = next->y - this->y;
        if (diff_y >=  0.0f && diff_y <= 0.1f && diff_x <=  0.05f && diff_x >= -0.05f) {
           return;
        }
    }
    y += speed; // Przesunięcie w górę
}

void Rectangel::moveDown() {
    for (auto& next : Rectangel::objects) {
        if (this == next) continue;
        float diff_x = next->x - this->x;
        float diff_y = next->y - this->y;
        if (diff_y <=  0.0f && diff_y >= -0.1f && diff_x >= -0.05f && diff_x <= 0.05f) {
            return;
        }
    }
    y -= speed; // Przesunięcie w dół
}

void Rectangel::move() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    while (life != 0 && !stopFlag) {
        if (x <= 0.6f && y >= 0.50f && !stop) {
            moveRight();
            lifeDecreased = true;
        } else if (x >= 0.6f && y >= -0.50f && !stop) {
            moveDown();
        } else if (x >= -0.6f && y <= -0.50f&& !stop) {
            moveLeft();
        } else if (x <= -0.6f && y <= 0.50f && !stop) {
            moveUp();
            if (lifeDecreased) {
                lifeDecreased = false;
                life--;
            }
        }
        stop = false;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    auto it = find(objects.begin(), objects.end(), this);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void drawScene() {

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,0.0f,1.0f); 

    // Ustawienie szerokości linii
    glLineWidth(2.0f);

    // Rozpoczęcie rysowania pustego prostokąta
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7f, -0.57f); // Lewy dolny róg
    glVertex2f(0.7f, -0.57f);  // Prawy dolny róg
    glVertex2f(0.7f, 0.57f);   // Prawy górny róg
    glVertex2f(-0.7f, 0.57f);  // Lewy górny róg
    glEnd();

    // Rozpoczęcie rysowania mniejszego prostokąta w środku
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, -0.4f); // Lewy dolny róg
    glVertex2f(0.5f, -0.4f);  // Prawy dolny róg
    glVertex2f(0.5f, 0.4f);   // Prawy górny róg
    glVertex2f(-0.5f, 0.4f);  // Lewy górny róg
    glEnd();

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    //Rozpoczęcie rysowania 3 prostokątu
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.3f, -0.8f); // Lewy dolny róg
    glVertex2f(0.3f, -0.8f);  // Prawy dolny róg
    glVertex2f(0.3f, 0.8f);   // Prawy górny róg
    glVertex2f(-0.3f, 0.8f);  // Lewy górny róg
    glEnd();
    //4 prostokąt
    //Rozpoczęcie rysowania 3 prostokątu
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2f, -0.7f); // Lewy dolny róg
    glVertex2f(0.2f, -0.7f);  // Prawy dolny róg
    glVertex2f(0.2f, 0.7f);   // Prawy górny róg
    glVertex2f(-0.2f, 0.7f);  // Lewy górny róg
    glEnd();

    glFlush();
}

int random_time_in_seconds(int min_time, int max_time) {
    // Inicjalizacja generatora liczb losowych
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Określenie zakresu losowania
    std::uniform_int_distribution<int> dist(min_time, max_time);
    
    // Wylosowanie czasu w milisekundach z podanego zakresu
    return dist(gen);
}
vector<thread> threads;

void addNewThread(){
    while (!stopFlag)
    {
        std::this_thread::sleep_for(std::chrono::seconds(random_time_in_seconds(5,6)));

        // Sprawdź, czy którykolwiek obiekt znajduje się w określonym przedziale x
        bool objectInRange = false;
        for(auto& car : Rectangel::objects){
            if(car->x >= -0.8f && car->x <= -0.7f){
                objectInRange = true;
                break; // Przerwij pętlę, jeśli znaleziono obiekt w zakresie
            }
        }

        // Dodaj nowy wątek tylko jeśli nie ma obiektu w określonym przedziale x
        if (!objectInRange) {
            Rectangel* rec = new Rectangel(-0.80f, 0.5f, Rectangel::random_speed(0.001f, 0.01f), Color::random_color());
            threads.emplace_back(&Rectangel::move, rec);
            Rectangel::objects.push_back(rec);
        }

    }
    
}

void render(){

    drawScene();
    if(!Rectangel::objects.empty()){
        cout << Rectangel::objects.front()->y<<endl;
    }
    for( auto& obj : Rectangel::objects){
        obj->draw();

    }

}

int main() {
    GLFWwindow* window;

    // Inicjalizacja biblioteki GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Utworzenie okna
    window = glfwCreateWindow(1500, 900, "Pusty prostokąt w GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Ustawienie kontekstu OpenGL dla okna
    glfwMakeContextCurrent(window);
    
    // Ustawienie koloru tła na biały
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    thread main_thread(addNewThread);

    // Pętla główna programu
    while (!glfwWindowShouldClose(window)) {
        // Wyczyszczenie bufora koloru
        glClear(GL_COLOR_BUFFER_BIT);
        
        render();
        
        // Wyświetlenie na ekranie
        glfwSwapBuffers(window);

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
             cout << "Space key pressed. Stopping...\n";
             break;
        }

        
        
        // Obsługa zdarzeń
        glfwPollEvents();
    }

    stopFlag = true;

    main_thread.join();

    for(auto& rec : threads){
        rec.join();
    }
    // Zakończenie programu
    glfwTerminate();
    return 0;
}
