#include <Siv3D.hpp>

void Main()
{
    while (System::Update()){
        const double hue = Scene::Time() * 60;
        Scene::SetBackground(HSV{hue});
        
        for (int i = 0; i < 7; ++i){
            Circle{100+100*i, 200, 40}.draw(HSV{i*50});
        }
        
        double radious = Scene::Time() * 5;
        if (radious > 300) radious -= 300;
        Circle{Cursor::Pos(), radious}.draw(HSV{hue+180, 0.8});
    }
}
