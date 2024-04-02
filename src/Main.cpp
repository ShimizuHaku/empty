#include <Siv3D.hpp>

void Main()
{
    Scene::SetBackground(ColorF{1,1,1,1});
    Window::SetStyle(WindowStyle::Sizable);
    
    const Font h1{FontMethod::MSDF, 80, Typeface::Medium};
    const Font h3{FontMethod::MSDF, 40, Typeface::Regular};
    
    int current_scene = 0;
    
    bool init = false;
    
    Array<int> la(12);
    for (int i = 0; i < 12; ++i) la[i] = i;
    
    int target = 10;
    int seen = 2;
    
    bool prev = false;
    bool next = true;
    
    Array<int> llog, rlog;
    int l = 0, r = 11;
    int m = (l + r) / 2;
    
    auto init_all = [&](){
        seen = -1;
        target = 9;
        for (int i = 0; i < 12; ++i) la[i] = i;
        init = true;
        l = -1; r = 12; m = (l+r)/2;
        llog.clear(); rlog.clear();
        llog.push_back(-1); rlog.push_back(12);
    };
    
    
    
    while(System::Update())
    {
        const Vec2 center = Scene::Center();
        
        switch (current_scene) {
            case 0:
                h1(U"アルゴリズムで遊ぼう!!").drawAt(70,center-Vec2{0,200}, ColorF{0,0,0,1});
                
                if (SimpleGUI::Button(U"線形探索", center + Vec2{-280,-100}, 200)){
                    current_scene = 1;
                }
                if (SimpleGUI::Button(U"二分探索", center + Vec2{100,-100}, 200)){
                    current_scene = 2;
                }
                if (SimpleGUI::Button(U"線形探索", center + Vec2{-280,0}, 200)){
                    current_scene = 1;
                }
                if (SimpleGUI::Button(U"二分探索", center + Vec2{100,0}, 200)){
                    current_scene = 2;
                }
                
                if (!init) init_all();
                break;
                
            case 1:
                init = false;
                
                h1(U"線形探索").drawAt(70, center - Vec2{0,200}, ColorF{0,0,0,1});
                h3(U"target = ", target).drawAt(30, center - Vec2{200,80}, ColorF{0});
                
                if(SimpleGUI::Button(U"󰁍 Quit", Vec2{50,50})){
                    current_scene = 0;
                }
                
                for (int i = 0; i < 12; ++i){
                    RectF rect{30+i*60,center.y,60,60};
                    
                    if (i <= seen) {
                        rect.draw(ColorF{0.2,0.4,0.8,1.0});
                        rect.drawFrame(2,0,ColorF{0});
                        h3(i).draw(24, rect.stretched(-10),ColorF(1.0));
                    }
                    if(i == target){
                        rect.draw(ColorF{0.8,0.2,0.2,1.0});
                        rect.drawFrame(2,0,ColorF{0});
                        h3(i).draw(24, rect.stretched(-10),ColorF(1.0));
                    }
                    if(i > seen){
                        rect.draw(ColorF{1.0});
                        rect.drawFrame(2,0,ColorF{0});
                        h3(i).draw(24, rect.stretched(-10),ColorF(0));
                    }
                }
                
                if (SimpleGUI::Button(U"Prev", center+Vec2{-150,-50}, unspecified, prev)){
                    seen--;
                }
                
                if (SimpleGUI::Button(U"Next", center+Vec2{100,-50}, unspecified, next)){
                    seen++;
                }
                
                prev = seen == -1 ? false : true;
                next = seen == target ? false : true;
                
                h3(U"線形探索は、たくさんのデータから\n目的のデータを見つけるアルゴリズムです。\n左から順に探索します。\n最悪計算量は比較的多くなります。")
                    .drawAt(36,center + Vec2{0,180}, ColorF{0,0,0,1});
                
                break;
            
            case 2:
                init = false;
                
                h1(U"二分探索").drawAt(70, center - Vec2{0,200}, ColorF{0,0,0,1});
                h3(U"target = ", target).drawAt(30, center - Vec2{200,80}, ColorF{0});
                
                if(SimpleGUI::Button(U"󰁍 Quit", Vec2{50,50})){
                    current_scene = 0;
                }
                
                for (int i = 0; i < 12; ++i){
                    RectF rect{30+i*60,center.y,60,60};
                    
                    if (i <= l || r <= i) {
                        rect.draw(ColorF{0.2,0.4,0.8,1.0});
                        rect.drawFrame(2,0,ColorF{0});
                        h3(i).draw(24, rect.stretched(-10),ColorF(1.0));
                    }
                    if(l == target && r == target && i == target){
                        rect.draw(ColorF{0.8,0.2,0.2,1.0});
                        rect.drawFrame(2,0,ColorF{0});
                        h3(i).draw(24, rect.stretched(-10),ColorF(1.0));
                    }
                    else if(i < r && l < i){
                        rect.draw(ColorF{1.0});
                        rect.drawFrame(2,0,ColorF{0});
                        h3(i).draw(24, rect.stretched(-10),ColorF(0));
                    }
                }
                
                if (SimpleGUI::Button(U"Prev", center+Vec2{-150,-50}, unspecified, prev)){
                    llog.pop_back(); rlog.pop_back();
                    l = llog.back(); r = rlog.back();
                    m = (l + r) / 2;
                }
                
                if (SimpleGUI::Button(U"Next", center+Vec2{100,-50}, unspecified, next)){
                    if (m < target) l = m;
                    else if (m > target) r = m;
                    else l = r = m;
                    llog.push_back(l); rlog.push_back(r);
                    m = (l + r)/2;
                }
                
                if (llog.size() == 1) prev = false;
                else prev = true;
                
                if (l == r) next = false;
                else next = true;
                
                h3(U"二分探索は、たくさんのデータから\n目的のデータを見つけるアルゴリズムです。\n一度に半分のデータを探索範囲から除外します。\n最悪計算量はとても少ないです。")
                    .drawAt(36,center + Vec2{0,180}, ColorF{0,0,0,1});
            
            break;
            default:
                break;
        }
        
    }
}
