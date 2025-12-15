#include <iostream>
#include <string>
using namespace std;

struct Question {
    string text;
    string optionA;
    string optionB;
    string traitA;
    string traitB;
    Question* next;
};

Question* createQuestion(string t, string a, string b,
                         string ta, string tb) {
    Question* q = new Question();
    q->text = t;
    q->optionA = a;
    q->optionB = b;
    q->traitA = ta;
    q->traitB = tb;
    q->next = NULL;
    return q;
}

void showHeader() {
    cout << "\n============================================\n";
    cout << "        PERSONALITY QUIZ ENGINE\n";
    cout << "============================================\n";
    cout << "Answer honestly. Choose A or B only.\n";
    cout << "--------------------------------------------\n";
}

void showFooter() {
    cout << "\n============================================\n";
    cout << "        QUIZ COMPLETED\n";
    cout << "============================================\n";
    cout << "Personality evaluation will be shown soon.\n";
}

int main() {
    // Creating questions
    Question* q1 = createQuestion(
        "In a group discussion, you usually:",
        "Listen and observe",
        "Take charge and speak up",
        "Introversion", "Leadership");

    Question* q2 = createQuestion(
        "When facing a problem, you prefer:",
        "Analyzing facts and data",
        "Thinking creatively for new ideas",
        "Logic", "Creativity");

    Question* q3 = createQuestion(
        "At social events, you feel more comfortable:",
        "Staying with a few close people",
        "Meeting many new people",
        "Introversion", "Leadership");

    Question* q4 = createQuestion(
        "Your decisions are mostly based on:",
        "Logical reasoning",
        "Creative instincts",
        "Logic", "Creativity");

    Question* q5 = createQuestion(
        "When working in a team, you like to:",
        "Support quietly",
        "Lead and organize",
        "Introversion", "Leadership");

    Question* q6 = createQuestion(
        "You enjoy tasks that require:",
        "Clear structure",
        "Imagination and freedom",
        "Logic", "Creativity");

    Question* q7 = createQuestion(
        "People describe you as:",
        "Calm and reserved",
        "Confident and assertive",
        "Introversion", "Leadership");

    Question* q8 = createQuestion(
        "When learning something new, you prefer:",
        "Step-by-step guidance",
        "Exploring on your own",
        "Logic", "Creativity");

    Question* q9 = createQuestion(
        "In stressful situations, you usually:",
        "Think quietly",
        "Take control",
        "Introversion", "Leadership");

    Question* q10 = createQuestion(
        "You trust decisions that are:",
        "Well-reasoned",
        "Innovative",
        "Logic", "Creativity");

    Question* q11 = createQuestion(
        "In a team, you mostly:",
        "Work independently",
        "Guide others",
        "Introversion", "Leadership");

    Question* q12 = createQuestion(
        "You prefer tasks that are:",
        "Predictable",
        "Open-ended",
        "Logic", "Creativity");

    Question* q13 = createQuestion(
        "When sharing ideas, you:",
        "Think before speaking",
        "Speak confidently",
        "Introversion", "Leadership");

    Question* q14 = createQuestion(
        "You enjoy problems that:",
        "Have clear solutions",
        "Allow multiple interpretations",
        "Logic", "Creativity");

    Question* q15 = createQuestion(
        "Your natural role in a group is:",
        "Observer",
        "Leader",
        "Introversion", "Leadership");

    // Linking list
    q1->next = q2;   q2->next = q3;   q3->next = q4;
    q4->next = q5;   q5->next = q6;   q6->next = q7;
    q7->next = q8;   q8->next = q9;   q9->next = q10;
    q10->next = q11; q11->next = q12; q12->next = q13;
    q13->next = q14; q14->next = q15;

    showHeader();

    Question* current = q1;
    int qNo = 1;
    char choice;

    while (current != NULL) {
        cout << "\n--------------------------------------------\n";
        cout << "Question " << qNo << " / 15\n\n";
        cout << current->text << "\n\n";
        cout << "  A) " << current->optionA << "\n";
        cout << "  B) " << current->optionB << "\n";
        cout << "\nYour choice (A/B): ";
        cin >> choice;

        if (choice == 'A' || choice == 'a')
            cout << "? Trait noted: " << current->traitA << "\n";
        else if (choice == 'B' || choice == 'b')
            cout << "? Trait noted: " << current->traitB << "\n";
        else
            cout << "? Invalid input, moving ahead.\n";

        current = current->next;
        qNo++;
    }

    showFooter();
    return 0;
}

