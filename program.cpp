#include <GLFW/glfw3.h>
#include <thread>
#include <random>
#include <atomic>
#include <iostream>
#include <mutex>

std::mutex mtx; // Deklaracja obiektu mutex

using namespace std;

atomic<bool> flag(false);


random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis_delay(8,10);


// Struktura reprezentująca kolor w formacie RGB
struct Color {
    float r, g, b;

    Color(float red, float green, float blue) : r(red), g(green), b(blue) {}

};

// Funkcja generująca losowy kolor
Color generateRandomColor() {
    // Inicjalizacja generatora liczb pseudolosowych
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f); // Losowanie z przedziału [0.0, 1.0]

    // Losowanie składowych koloru
    float red = dis(gen);
    float green = dis(gen);
    float blue = dis(gen);

    // Zwrócenie wylosowanego koloru
    return Color(red, green, blue);
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Ustawienie koloru na biały z przezroczystością

   

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
struct CarVertical{
    float speed;
    float Xposistion;
    float Yposition;
    Color color;

    CarVertical() = default;

    CarVertical(float initialXposistion, float initialYposition, const Color& initialColor)
        : Xposistion(initialXposistion), Yposition(initialYposition),
           color(initialColor) {}

    void draw(){
            glColor3f(color.r, color.g, color.b);

            glBegin(GL_QUADS);
            glVertex2f(Xposistion - 0.52f, Yposition + 0.42f); // Lewy dolny róg
            glVertex2f(Xposistion - 0.58f, Yposition + 0.42f);  // Prawy dolny róg
            glVertex2f(Xposistion - 0.58f, Yposition + 0.48f);   // Prawy górny róg
            glVertex2f(Xposistion - 0.52f, Yposition + 0.48f);  // Lewy górny róg

            glEnd();

    }

    void moveRight() {
        Xposistion += speed;
    }

    void moveLeft() {
        Xposistion -= speed;
    }

    void moveDown(){
        Yposition -= speed;
    }

    void moveUp(){
        
        Yposition += speed;
        
    }

    void drive() {

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        while (!flag)
        {
            
             if (Xposistion >= 0.8f && Yposition >= -1.18f) {
                moveDown();  
            }
            else if(Xposistion >= 0.30f && Yposition <= -1.18f){
                moveLeft();
            }
            else if(Xposistion <= 0.32f && Yposition <= 0.3f){
                moveUp();
            }
            else if(Xposistion <= 0.8f && Yposition >= 0.3f){
                moveRight();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
                
        
    }



};

class Car{

    private:
        float speed;
        float Xposistion;
        float Yposition;
        int life;
        bool lifeDecreased;
        Color color;

    public:    
    
    Car(float initialXposistion, float initialYposition, int initialLife, bool initialLifeDecreased, const Color& initialColor)
        : Xposistion(initialXposistion), Yposition(initialYposition),
          life(initialLife), lifeDecreased(initialLifeDecreased), color(initialColor) {}


    void drawCar(){
       
        if(life != 0){
            glColor3f(color.r, color.g, color.b);

            glBegin(GL_QUADS);
            glVertex2f(Xposistion - 0.52f, Yposition + 0.42f); // Lewy dolny róg
            glVertex2f(Xposistion - 0.58f, Yposition + 0.42f);  // Prawy dolny róg
            glVertex2f(Xposistion - 0.58f, Yposition + 0.48f);   // Prawy górny róg
            glVertex2f(Xposistion - 0.52f, Yposition + 0.48f);  // Lewy górny róg

            glEnd();
        }
        

    }

    void moveRight() {
        Xposistion += speed;
    }

    void moveLeft() {
        Xposistion -= speed;
    }

    void moveDown(){
        Yposition -= speed;
    }

    void moveUp(){
        Yposition += speed;
    }
    // Settery
    void setSpeed(float newSpeed) {
        speed = newSpeed;
    }

    void setXPosition(float newXPosition) {
        Xposistion = newXPosition;
    }

    void setYPosition(float newYPosition) {
        Yposition = newYPosition;
    }

    void setLife(int newLife) {
        life = newLife;
    }

    void setLifeDecreased(bool newLifeDecreased) {
        lifeDecreased = newLifeDecreased;
    }

    void setColor(const Color& newColor) {
        color = newColor;
    }

    // Gettery (opcjonalnie)
    float getSpeed() const {
        return speed;
    }

    float getXPosition() const {
        return Xposistion;
    }

    float getYPosition() const {
        return Yposition;
    }

    int getLife() const {
        return life;
    }

    bool getLifeDecreased() const {
        return lifeDecreased;
    }

    const Color& getColor() const {
        return color;
    }

    void drive() {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        while (life != 0 && !flag) {
            
            if (Xposistion <= 1.10f && Yposition >= 0.00f) {
                mtx.lock();
                moveRight();
                lifeDecreased = true;
                mtx.unlock();
            } else if (Xposistion>= 1.10f && Yposition >= -0.90f) {
                mtx.lock();
                moveDown();
                mtx.unlock();
            } else if (Xposistion >= 0.0f && Yposition <= -0.90f) {
                mtx.lock();
                moveLeft();
                mtx.unlock();
            } else if (Xposistion <= 0.0f && Yposition <= 0.0f) {
                mtx.lock();
                moveUp();
                if (lifeDecreased) {
                    lifeDecreased = false;
                    life--;
                }
                mtx.unlock();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
    }
   

};

Car& generateCar() {
    Color color = generateRandomColor();
    Car& car = *(new Car(0.0f, 0.0f, 3, true, color));

    // Lokalny generator liczb losowych
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis_speed(0.008f, 0.03f);

    // Ustawienie prędkości
    car.setSpeed(dis_speed(gen));

    return car;
}

CarVertical generateCarVeritcal(){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis_step(0.0f, 1.0f);
        

        // Wylosowanie liczby z przedziału [0, 1]
        float randomNumber = dis_step(gen);

        Color color = generateRandomColor();
        
        float randomStep;
        if (randomNumber < 0.5f) {
            std::uniform_real_distribution<float> dis_location(0.3f, -1.2f);
            CarVertical carVertical(0.8f,dis_location(gen),color);
            carVertical.speed = 0.02f;
            return carVertical;
        } else {
            std::uniform_real_distribution<float> dis_location(0.25f, -1.2f);
            CarVertical carVertical(0.3f,dis_location(gen),color); 
            carVertical.speed = 0.02f;
            return carVertical;
        }
        // 0.3 0.3
        // 0.3 -1.2
        // 0.8f
    
};

// void drive(Car &car){

//         // if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//         //     std::cout << "Space key pressed. Stopping...\n";
//         //     break;
//         // }

//         std::this_thread::sleep_for(std::chrono::milliseconds(300));
//         while(car.getLife() != 0 && !flag){

           
           
//             if(car.getXPosition() <= 1.10f && car.getYPosition() >= 0.00f){
                
//                 car.moveRight();
//                 car.setLifeDecreased(true);
                
//             }
            
            
//             else if(car.getXPosition() >= 1.10f && car.getYPosition() >= -0.90f){
                
//                 car.moveDown();
                
//             }
            
//             else if(car.getXPosition() >= 0.0f && car.getYPosition() <= -0.90f){
                
//                 car.moveLeft();
                
//             }

//             else if(car.getXPosition() <= 0.0f && car.getYPosition() <= 0.0f ){
                
//                 car.moveUp();

//                 if(car.getLifeDecreased()){
//                     car.setLifeDecreased(false);
                
//                     car.setLife(car.getLife() - 1);
                    
//                 }
                

//             }

//             std::this_thread::sleep_for(std::chrono::milliseconds(10));
//         }
        

      
        
//     }
void render(vector<Car> &cars){
    glClear(GL_COLOR_BUFFER_BIT);
    drawScene();
    
    for(Car& car : cars){
        
        car.drawCar();
    }
    
    glFlush();
}



void addCarThread(vector<thread>& carThreads, vector<Car>& cars) {
    int itr = 0;
    while (!flag) {
        
        this_thread::sleep_for(chrono::seconds(dis_delay(gen)));
        
        
        mtx.lock();
        Car newCar = generateCar();
        mtx.unlock();

        cars.push_back(newCar);
        
        carThreads.emplace_back(&Car::drive, ref(cars[itr]));

        mtx.lock();
        itr++;
        mtx.unlock();

       // this_thread::sleep_for(chrono::seconds(3)); // Interwał dodawania nowych wątków
        

    }
}

int main() {
    GLFWwindow* window;

    // Inicjalizacja biblioteki GLFW
    if (!glfwInit())
        return -1;

    // Utworzenie okna
    window = glfwCreateWindow(1500, 900, "Pusty prostokąt w GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis_speed(0.00005f, 0.005f);
    uniform_int_distribution<int> dis_delay(3,60);
    
    // Ustawienie kontekstu OpenGL
    glfwMakeContextCurrent(window);

    // Umożliwienie przezroczystości
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    vector<Car> cars; // Kontener dynamiczny przechowujący samochody
    vector<thread> carThreads;

    thread CarAdder(addCarThread, ref(carThreads), ref(cars)); // Dodanie wątku dodającego wątki dodające pojazdy
    CarVertical car1 = generateCarVeritcal();
    CarVertical car2 = generateCarVeritcal();
    CarVertical car3 = generateCarVeritcal();
    Car c = generateCar();
    c.setSpeed(0.001f);

    thread car1Vertical(&CarVertical::drive, &car1);
    thread car2Vertical(&CarVertical::drive, &car2);
    thread car3Vertical(&CarVertical::drive, &car3);
    thread  threadC(&Car::drive, &c);

    while (!glfwWindowShouldClose(window)) {
        render(cars);
        car1.draw();
        car2.draw();
        car3.draw();
         c.drawCar();
        glfwSwapBuffers(window);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
             cout << "Space key pressed. Stopping...\n";
             break;
        }
        
        glfwPollEvents();
    }

    flag = true;
    CarAdder.join();

    for (auto& t : carThreads) {
        t.join(); // Czekaj na zakończenie wątków
    }
    car1Vertical.join();
    car2Vertical.join();
    car3Vertical.join();
    threadC.join();

    cout<< "koniec" << endl;

    
    // Zakończenie pracy GLFW
   
    
    glfwTerminate();
    return 0;
}
//pojazdy się nie wyprzedzają, zatrzymania na skrzyżowaniu
