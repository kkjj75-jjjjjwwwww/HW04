// main.cpp 
// Unreal 8기 김종원 4번 과제

#include <iostream>
#include <vector>
#include <string>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
private:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경
    //[김종원] public 멤버 변수를 private으로 변경하고 getter를 추가하여 캡슐화 적용
public:
    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
    const std::string& GetPotionName() const {
        return potionName;
    }
    const std::vector<std::string>& GetIngredients() const {
        return ingredients;
    } //[김종원]private 멤버변수 getter 생성
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.emplace_back(name, ingredients);
    //[김종원]:push_back 대신 emplace_back을 사용, 만들어진 객체가 아닌 새로운 객체를 만드는 과정에서 저장하고 있기때문 
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다.\n" << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다.\n" << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;

        for (const auto& recipe : recipes) {
            std::cout << "- 물약 이름: " << "[" << recipe.GetPotionName() << "]" << std::endl;
            std::cout << " > 필요 재료: ";
            // 재료 목록을 순회하며 출력 -> [김종원] index for를 range-for로 변경 (가독성 개선)
            
            for (const auto& ingredient : recipe.GetIngredients()) {
                std::cout << "[" << ingredient << "]";
                // 마지막 재료가 아니면 쉼표로 구분 -> [김종원] "[]"로 수정
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "---------------------------\n";
    }
    void FindRecipeByName(const std::string& name) const
    {
        bool bFound = false;
        std::cout << "\n--- [ 검색된 레시피 목록 ] ---" << std::endl;
        for (const auto& recipe : recipes) {
            if (name == recipe.GetPotionName()) {
                std::cout << "- 물약 이름: " << "[" << recipe.GetPotionName() << "]" << std::endl;
                std::cout << " > 필요 재료: ";

                for (const auto& ingredientname : recipe.GetIngredients()) {
                    std::cout << "[" << ingredientname << "]";
                }
                std::cout << "\n---------------------------\n" << std::endl;
                bFound = true;
            }
        }
        if (!bFound) {
            std::cout << "검색된 레시피가 없습니다.\n---------------------------\n" << std::endl;
        }
    } //[김종원] 물약 이름으로 검색 기능 추가

    void FindIngredientByName(const std::string& name) const
    {
        bool bFound = false;
        std::cout << "\n--- [ 검색된 레시피 목록 ] ---" << std::endl;
        for (const auto& recipe : recipes) {
            for (const auto& ingredient : recipe.GetIngredients()) {
                if (name == ingredient) {
                    std::cout << "- 물약 이름: " << "[" << recipe.GetPotionName() << "]" << std::endl;
                    std::cout << " > 필요 재료: ";

                    for (const auto& ingredientName : recipe.GetIngredients()) {
                        std::cout << "[" << ingredientName << "]";
                    }
                    std::cout << "\n---------------------------\n" << std::endl;
                    bFound = true;
                }
            }

        }
        if (!bFound) {
            std::cout << "검색된 레시피가 없습니다.\n---------------------------\n" << std::endl;
        }
    } //[김종원] 재료명으로 검색 기능 추가
};

int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        std::cout << "연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 검색" << std::endl;
        std::cout << "4. 재료명으로 물약 검색" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";
        //[김종원]:물약과 재료로 검색 가능하도록 메뉴 추가

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::string name;
            std::cout << "검색할 물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            myWorkshop.FindRecipeByName(name);
            // [김종원]물약 이름으로 검색
        }
        else if (choice == 4) {
            std::string name;
            std::cout << "검색할 재료명: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            myWorkshop.FindIngredientByName(name);
            // [김종원]재료명으로 검색
        }
        else if (choice == 5) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}