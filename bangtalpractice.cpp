#include <bangtal>
using namespace bangtal;

int main()
{
    //장면생성
    auto scene1 = Scene::create("방1", "Images/배경-1.png");
    auto scene2 = Scene::create("방2", "Images/배경-2.png");

    //제한시간 생성
    auto timer = Timer::create(20);
    showTimer(timer);
    timer->start();

    timer->setOnTimerCallback([&](TimerPtr timer)->bool {     
        showMessage("탈출 실패ㅠㅠ");
        endGame();
        return true;
        });

    //가짜문 생성
    auto door2 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 1100, 220);

    //진짜문 생성
    auto door1 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 800, 270);

    //열쇠 생성
    auto key = Object::create("Images/열쇠.png", scene1, 600, 150);
    key->setScale(0.2f);
    //열쇠를 주워보자
    key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        key->pick();
        return true;
        });

    //화분 생성
    ObjectPtr flower = Object::create("Images/화분.png", scene1, 550, 150);
    auto move1 = false;
    //화분은 클릭하면 옆으로 옮겨진다.
    flower->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (action == MouseAction::MOUSE_DRAG_LEFT && move1 == false) {
            flower->locate(scene1, 400, 150);
            move1 = true;
        }
        else if (action == MouseAction::MOUSE_DRAG_RIGHT && move1 == false) {
            flower->locate(scene1, 650, 150);
            move1 = true;
        }
        return true;
        });

    bool open1 = false;

    door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//문이 닫혀있으면 문을 열고,열려있으면 다음방으로 간다.
        if (open1 == true) {
            scene2->enter();
        }
        else if (key->isHanded()) {
            open1 = true;
            door1->setImage("Images/문-오른쪽-열림.png");
            showMessage("문이 열렸다!");
        }
        else {
            showMessage("열쇠가 필요해보여....");
        }
        return true;
        });

    door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//가짜문은 그냥 열리지 않는다.
        showMessage("문이 열리지 않아 . . . . .");
        return true;
        });

    //두번째 방과 첫번째 방 사이의 문 생성
    auto door3 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
    door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//누르면 1번방으로 이동
        scene1->enter();
        return true;
        });

    //최종문 생성
    auto door4 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 910, 270, false);//숨겨진 문

    auto open2 = false;

    door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (open2 == true) {
            endGame();
        }
        else {
            door4->setImage("Images/문-오른쪽-열림.png");
            showMessage("문이 열렸어!!!!");
            open2 = true;
        }
        return true;
        });




    //스위치 생성
    auto button = Object::create("Images/버튼.png", scene2, 810, 450);
    button->setScale(0.1f);
    auto light = true;
    button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//클릭시 문이 닫혀있으면 메세지를 출력하고,열려있으면 게임을 종료한다.
        if (light) {
            scene2->setLight(0.2f);
            door4->show();
            light = false;
        }
        else {
            light = true;
            door4->hide();
            scene2->setLight(1);
        }
        return true;
        });

    auto flower2 = Object::create("Image/화분.png", scene2, 550, 300);

    startGame(scene1);//게임 시작!

    return 0;
}