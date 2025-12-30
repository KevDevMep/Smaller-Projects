#include <iostream> //Last edit at 2/11/23
#include <string_view>
#include <random>
#include <vector>
using namespace std;

enum class Card_Number
{
    ace,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine, 
    ten,
    jack,
    queen,
    king,
};
constexpr string_view getCard_Number(Card_Number card_number)
{
    using enum Card_Number;
    switch (card_number)
    {
    case ace: return "ace"; 
    case two:  return "two";
    case three:  return "three";    
    case four:   return "four";
    case five: return "five"; 
    case six:  return "six";
    case seven:  return "seven";
    case eight:  return "eight";    
    case nine:   return "nine";
    case ten: return "ten";
    case jack:  return "jack";
    case queen:  return "jack";
    case king:  return "jack";
    default:    return "???";
    };
};
enum class Card_Type
{
    spades,
    hearts,
    diamonds,
    clubs,
};
constexpr string_view getCard_Type(Card_Type card_type)
{
    using enum Card_Type;
    switch (card_type)
    {
    case diamonds: return "diamonds"; 
    case clubs:   return "clubs";
    case hearts:  return "hearts";
    case spades:  return "spades";
    default:    return "???";
    };
};

struct Card
{
    string_view card_number {};
    string_view card_type {};
};
void printHand (const vector<Card>& hand)
{
    for (const auto& x : hand) cout << "The card is " << x.card_number << " of " << x.card_type << '\n';
};

int main()
{
    mt19937 mt{ random_device{}() };    
    uniform_int_distribution die13{ 0, 12 };
    uniform_int_distribution die4{ 0, 3 };
    vector<Card> hand{};
    int n {};

    cout << "Cards\n";
    cout << "How many cards do you what to draw? ";
    cin >> n;
    for (int i {0}; i < n; i++)
    {
        Card_Number cardN{die13(mt)};
        Card_Type cardT{die4(mt)};
        Card card{getCard_Number(cardN), getCard_Type(cardT)};
        hand.push_back(card);
    }
    printHand(hand);

    return 0;
}