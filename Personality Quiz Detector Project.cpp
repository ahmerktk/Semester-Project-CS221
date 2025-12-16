#include <iostream>
#include <string>
using namespace std;

//   QUESTION LINKED LIST
struct Question {
    string text;
    string options[4];
    char traits[4];     // I, E, S, N, T, F, J, P
    Question* next;
};

Question* createQuestion(string t,string o1, char c1,string o2, char c2,string o3, char c3, string o4, char c4){
    Question* q = new Question();
    q->text = t;
    q->options[0] = o1; q->traits[0] = c1;
    q->options[1] = o2; q->traits[1] = c2;
    q->options[2] = o3; q->traits[2] = c3;
    q->options[3] = o4; q->traits[3] = c4;
    q->next = NULL;
    return q;
}

//  BST FOR TRAITS
struct TraitNode{
    char trait;
    int score;
    TraitNode* left;
    TraitNode* right;
};

TraitNode* createTrait(char t){
    TraitNode* node = new TraitNode();
    node->trait = t;
    node->score = 1;
    node->left = node->right = NULL;
    return node;
}

TraitNode* insertTrait(TraitNode* root, char t){
    if (root == NULL)
        return createTrait(t);

    if (t == root->trait)
        root->score++;
    else if (t < root->trait)
        root->left = insertTrait(root->left, t);
    else
        root->right = insertTrait(root->right, t);

    return root;
}

int getScore(TraitNode* root, char t){
    if (root == NULL) return 0;
    if (root->trait == t) return root->score;
    if (t < root->trait) return getScore(root->left, t);
    return getScore(root->right, t);
}


//   CONSOLE UI
void header() {
    cout << "\n============================================\n";
    cout << "        MBTI PERSONALITY QUIZ\n";
    cout << "============================================\n";
    cout << "Choose the option that feels most like you.\n";
    cout << "--------------------------------------------\n";
}

//	 PERSONALITY DESCRIPTION
void describe(string type) {
    cout << "\n============================================\n";
    cout << "        PERSONALITY INSIGHT\n";
    cout << "============================================\n";

    if (type == "INFP")
        cout << "You are empathetic, idealistic, creative, and deeply value meaning.\n";
    else if (type == "INTJ")
        cout << "You are strategic, analytical, independent, and future-oriented.\n";
    else if (type == "ENTJ")
        cout << "You are confident, decisive, and a natural leader.\n";
    else if (type == "ENFP")
        cout << "You are energetic, imaginative, and driven by values and people.\n";
    else if (type == "ISTJ")
        cout << "You are practical, responsible, and highly dependable.\n";
    else
        cout << "You have a balanced and adaptable personality.\n";
}


int main() {

    // Create Questions (10 – controlled & strong)
    Question* q1 = createQuestion(
        "In a new environment, you prefer to:",
        "Stay reserved and observe", 'I',
        "Engage and talk to others", 'E',
        "Plan everything early", 'J',
        "Keep things flexible", 'P'
    );

    Question* q2 = createQuestion(
        "You trust information that is:",
        "Based on facts and reality", 'S',
        "Based on patterns and ideas", 'N',
        "Logically sound", 'T',
        "Emotionally meaningful", 'F'
    );

    Question* q3 = createQuestion(
        "When making decisions, you rely more on:",
        "Objective analysis", 'T',
        "Personal values", 'F',
        "Past experiences", 'S',
        "Future possibilities", 'N'
    );

    Question* q4 = createQuestion(
        "Your daily life is usually:",
        "Well-organized", 'J',
        "Go-with-the-flow", 'P',
        "Quiet and focused", 'I',
        "Social and energetic", 'E'
    );

    Question* q5 = createQuestion(
        "You prefer work that:",
        "Has clear instructions", 'S',
        "Allows innovation", 'N',
        "Involves logic", 'T',
        "Helps people", 'F'
    );

    // Linked-list
    q1->next = q2;
    q2->next = q3;
    q3->next = q4;
    q4->next = q5;

    header();

    TraitNode* root = NULL;
    Question* current = q1;
    int qNo = 1;
    char choice;

    while (current != NULL) {
        cout << "\n--------------------------------------------\n";
        cout << "Question " << qNo++ << "\n\n";
        cout << current->text << "\n\n";

        for (int i = 0; i < 4; i++)
            cout << char('A' + i) << ") " << current->options[i] << "\n";

        cout << "\nYour choice (A-D): ";
        cin >> choice;

        int idx = choice - 'A';
        if (idx >= 0 && idx < 4)
            root = insertTrait(root, current->traits[idx]);
        else
            cout << "Invalid choice, skipped.\n";

        current = current->next;
    }

//  Build MBTI type
    string type = "";
    type += (getScore(root, 'I') >= getScore(root, 'E')) ? 'I' : 'E';
    type += (getScore(root, 'S') >= getScore(root, 'N')) ? 'S' : 'N';
    type += (getScore(root, 'T') >= getScore(root, 'F')) ? 'T' : 'F';
    type += (getScore(root, 'J') >= getScore(root, 'P')) ? 'J' : 'P';

    cout << "\n============================================\n";
    cout << "Your Personality Type: " << type << endl;

    describe(type);

    return 0;
}
