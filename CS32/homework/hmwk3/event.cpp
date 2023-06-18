// Aaron Chien
class Event 
{
    public:
        Event(string m_name) 
        {
            event_name = m_name;
        }
        virtual ~Event(){};
        // needs to be virtual
        // the dervied class would have already destructed the event object
        // so this virtual is telling the compiler not to destruct the event class twice when destructing dervied classes
        string name() const
        {
            return event_name;
        }
        virtual bool isSport() const
        {
            return true;
        }
        virtual string need() const = 0;
    private:
        string event_name;
};

class BasketballGame: public Event
{
    public:
        BasketballGame(string m_name): Event(m_name){};
        // there is no virtual constructor in inheritance, so we need initialization list 
        virtual string need() const
        // specialization of need function in base class
        {
            return "hoops";
        }
        virtual ~BasketballGame()
        // destructor used, needs to be virtual
        // same pattern for the rest of the inherited classes 
        {
            cout << "Destroying the " << name() << " basketball game" << endl;
        }
};

class HockeyGame: public Event
{
    public:
        HockeyGame(string m_name): Event(m_name){};
        virtual string need() const
        {
            return "ice";
        }
        virtual ~HockeyGame()
        {
            cout << "Destroying the " << name() << " hockey game" << endl;
        }

};

class Concert: public Event
{
    public:
        // so we're getting the name of the event's name
        // we have an additional argument of genre specifically for this class

        Concert(string m_name, string m_genre): Event(m_name)
        // use the base class and also add in the m_genre as this is a specialization of the class
        {
            genre = m_genre;
        }
        virtual string need() const
        {
            return "a stage";
        }
        virtual bool isSport() const
        {
            return false; 
        }
        virtual ~Concert()
        // because this is a derived class, we use virtual to tell the compiler that we have our own destructor 
        {
            cout << "Destroying the " << name() << " " << genre << " concert" << endl;
        }
    private:
        string genre;
};