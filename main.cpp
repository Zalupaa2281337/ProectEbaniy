#include <SFML/Graphics.hpp>
#include "Test.h"
#include <iostream>

using namespace sf;
using namespace std;

//Здесь стоится график
void Make_graphics(double x, int n, double k)
{
    //Количество пикселей между точками
    int Y_pix = int(x/900);
    int P_pix = int(1600/n);

    //Получаем значения платежей
    map<int,double> mp = MakeDifp(x,n,k);
    map<int,double> mp2 = MakeAnp(x,n,k);

    //Размеры окна
    int Size_w = 1920;
    int Size_H = 1080;

    //Создается окно
    RenderWindow window(VideoMode(Size_w, Size_H), "Grafics");
    window.setFramerateLimit(20);

    //Пока окно не закрто
    while (window.isOpen()) {
        Event event;

        //Закрытие окна
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        //Цвет окна
        window.clear(Color::White);

        //Полосы оси Х и Y
        RectangleShape rectangleY(Vector2f(10.f,float(Size_H)));
        RectangleShape rectangleX(Vector2f(float(Size_w),10.f));
        rectangleY.setFillColor(Color::Black);
        rectangleX.setFillColor(Color::Black);
        rectangleY.setPosition(5.f,0.f);
        rectangleX.setPosition(0.f,1065.f);

        //Треугольники на концах координат
        CircleShape trX(20.f,3);
        trX.setFillColor(Color::Black);
        trX.setPosition(1925.f,1050.f);
        trX.rotate(90.f);

        CircleShape trY(20.f,3);
        trY.setFillColor(Color::Black);
        trY.setPosition(-10.f,-5.f);

        window.draw(trX);
        window.draw(trY);
        window.draw(rectangleY);
        window.draw(rectangleX);

        //Текст
        Text text1;
        Font font;
        font.loadFromFile("/Users/a1/Desktop/C++/HelloSFML/ofont.ru_Arial.ttf");
        text1.setString(L"Аннуитетный платеж");
        text1.setPosition(1500,100);
        text1.setCharacterSize(30);
        text1.setFont(font);
        text1.setFillColor(Color::Black);

        //Текст
        Text text2;
        text2.setString(L"Дифферинцированный платеж");
        text2.setPosition(1500,150);
        text2.setCharacterSize(25);
        text2.setFont(font);
        text2.setFillColor(Color::Red);

        window.draw(text1);
        window.draw(text2);

        //Отрисовка цифр
        for(int i = 1; i<=n; ++i)
        {
            Text num;
            num.setString(to_string(i));
            num.setPosition(i*P_pix,1050);
            num.setCharacterSize(15);
            num.setFont(font);
            num.setFillColor(Color::Black);
            window.draw(num);
        }

        //Содание графика для платежа
        Vector2f cr(0.f,0.f);
        for(pair<int,double> p: mp)
        {
            if(p.first>1 && p.second>10000)
            {
                CircleShape s(3.f);
                s.setFillColor(Color::Black);
                s.setPosition(p.first * P_pix, Size_H - int(p.second / Y_pix));
                window.draw(s);
                if(cr != Vector2f(0.f, 0.f))
                {
                    sf::Vertex line[] =
                            {
                                    sf::Vertex(cr),
                                    sf::Vertex(s.getPosition())
                            };
                    line[0].color = Color::Black;
                    line[1].color = Color::Black;
                    window.draw(line,2,sf::Lines);

                }
                cr = s.getPosition();
            }
        }
        //Содание графика для платежа
        cr = Vector2f(0.f,0.f);
        for(pair<int,double> p: mp2)
        {
            if(p.first>1 && p.second>10000)
            {
                CircleShape s(3.f);
                s.setFillColor(Color::Red);
                s.setPosition(float(p.first * P_pix), Size_H - int(p.second / Y_pix));
                window.draw(s);
                if(cr != Vector2f(0.f, 0.f))
                {
                    sf::Vertex line[] =
                    {
                        sf::Vertex(cr),
                        sf::Vertex(s.getPosition())
                    };
                    line[0].color = Color::Red;
                    line[1].color = Color::Red;
                    window.draw(line,2,sf::Lines);

                }
                cr = s.getPosition();
            }
        }
        window.display();
    }

}
//Функция вывода меню
void out_Func()
{
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<"0.Выйти"<<endl;
    cout<<"1.Таблица аннуитетных платежей"<<endl;
    cout<<"2.Таблица дифференцируемых платежей"<<endl;
    cout<<"3.График двух платежей"<<endl;
}


int main() {

    double x;
    int n;
    double k;

    //Ввод чиел и их проверка
    cout<<"Введите сумму кредита"<<endl;
    cin>>x;
    if(cin.fail())
        throw runtime_error("Не верное значение");
    cout<<"Введите срок погашения кредита в месяцах"<<endl;
    cin>>n;
    if(cin.fail())
        throw runtime_error("Не верное значение");
    cout<<"Введите процентную плату"<<endl;
    cin>>k;
    if(cin.fail())
        throw runtime_error("Не верное значение");

    if(x>= 2147483647 || n>100 || k>= 100 || x <= 0 || n<=0 || k<=0){
        throw runtime_error("Не верное значение");
    }

    //Вывод меню
    out_Func();

    //Меню
    int i =1;
    while(i!= 0)
    {
        cin>>i;
        switch (i) {
            case 1:
                OutAnP(x,n,k);
                out_Func();
                break;
            case 2:
                OutDifP(x,n,k);
                out_Func();
                break;
            case 3:
                Make_graphics(x,n,k);
                out_Func();
                break;
            default:
                cout<<"Неверное число"<<endl;
        }
    }


    return  0;
}
