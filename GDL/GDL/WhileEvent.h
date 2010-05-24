#ifndef WHILEEVENT_H
#define WHILEEVENT_H

#include <boost/shared_ptr.hpp>
#include "Event.h"
class RuntimeScene;
class ObjectsConcerned;
class Instruction;
class Evaluateur;
class TiXmlElement;

/**
 * While event is a standard event that is repeated while conditions are true
 */
class WhileEvent : public BaseEvent
{
    public:
        WhileEvent() {};
        WhileEvent(const WhileEvent & event);
        virtual ~WhileEvent() {};

        WhileEvent& operator=(const WhileEvent & event);
        virtual BaseEventSPtr Clone() { return boost::shared_ptr<BaseEvent>(new WhileEvent(*this));}

        virtual bool IsExecutable() const {return true;}
        virtual void Execute( RuntimeScene & scene, ObjectsConcerned & objectsConcerned );

        virtual bool CanHaveSubEvents() const {return true;}
        virtual const vector < BaseEventSPtr > & GetSubEvents() const {return events;};
        virtual vector < BaseEventSPtr > & GetSubEvents() {return events;};
        void SetSubEvents(vector < BaseEventSPtr > & subEvents_) {events = subEvents_;};

        const vector < Instruction > & GetConditions() const { return conditions; };
        vector < Instruction > & GetConditions() { return conditions; };
        void SetConditions(vector < Instruction > & conditions_) { conditions = conditions_; };

        const vector < Instruction > & GetActions() const { return actions; };
        vector < Instruction > & GetActions() { return actions; };
        void SetActions(vector < Instruction > & actions_) { actions = actions_; };

        const vector < Instruction > & GetWhileConditions() const { return whileConditions; };
        vector < Instruction > & GetWhileConditions() { return whileConditions; };
        void SetWhileConditions(vector < Instruction > & whileConditions_) { whileConditions = whileConditions_; };

        virtual vector < vector<Instruction>* > GetAllConditionsVectors();
        virtual vector < vector<Instruction>* > GetAllActionsVectors();

        virtual void SaveToXml(TiXmlElement * eventElem) const;
        virtual void LoadFromXml(const TiXmlElement * eventElem);

#if defined(GDE)
        /**
         * Called when user click on the event
         */
        virtual void OnSingleClick(int x, int y, vector < boost::tuple< vector < BaseEventSPtr > *, unsigned int, vector < Instruction > *, unsigned int > > & eventsSelected,
                                 bool & conditionsSelected, bool & instructionsSelected);

        /**
         * Called when the user want to edit the event
         */
        virtual void EditEvent(wxWindow* parent_, Game & game_, Scene & scene_, MainEditorCommand & mainEditorCommand_);
#endif

    private:
        void Init(const WhileEvent & event);
        bool ExecuteWhileConditions( RuntimeScene & scene, ObjectsConcerned & objectsConcerned );
        bool ExecuteConditions( RuntimeScene & scene, ObjectsConcerned & objectsConcerned );
        void ExecuteActions( RuntimeScene & scene, ObjectsConcerned & objectsConcerned );

        vector < Instruction > whileConditions;
        vector < Instruction > conditions;
        vector < Instruction > actions;
        vector < BaseEventSPtr > events;

#ifdef GDE
        virtual void RenderInBitmap() const;
        mutable unsigned int whileConditionsHeight;

        int GetConditionsHeight() const;
        int GetActionsHeight() const;
        int GetWhileConditionsHeight() const;
#endif
};

#endif // WHILEEVENT_H