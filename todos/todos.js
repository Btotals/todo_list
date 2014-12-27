Tasks = new Mongo.Collection("tasks");

if (Meteor.isClient) {
    Template.body.helpers({
        tasks: function() {
            // console.log(Tasks.find());
            if (Session.get('hideCompleted')) {
                return Tasks.find({checked: {$ne: true}}, {sort: {date: -1}});
            } else {
                return Tasks.find({}, {sort: {date: -1}});
            }
        },
        hideCompleted: function() {
            return Session.get('hideCompleted');
        },
        incompleteCount: function() {
            return Tasks.find({checked: {$ne: true}}).count();
        }
    });

    Template.body.events({
        'submit .new-task': function(event) {
            var target = event.target || event.srcElement;
            var text = target[0].value;
            // Tasks.insert({
            //     text: text,
            //     date: new Date(),
            //     owner: Meteor.userId(),
            //     username: Meteor.user().username
            // });
            Meteor.call("addTask", text);
        },
        'change .hide-completed input': function(event) {
            Session.set("hideCompleted", event.target.checked);
        }
    });

    Template.task.events({
        'click .toggle-checked': function() {
            // Tasks.update(this._id, {
            //     $set: {
            //         checked: !this.checked
            //     }
            // });
            Meteor.call("setCheck", this._id, !this.checked);
        },
        'click .delete': function() {
            if (this.checked) {
                // Tasks.remove(this._id);
                Meteor.call("deleteTask", this._id);
            }
        }
    });
    Accounts.ui.config({
        passwordSignupFields: "USERNAME_ONLY"
    });
}

Meteor.methods({
    addTask: function(text) {
        if (!Meteor.userId()) {
            throw new Meteor.Error("not-authorized");
        }
        Tasks.insert({
            text: text,
            date: new Date(),
            owner: Meteor.userId(),
            username: Meteor.user().username
        });
    },
    deleteTask: function(taskId) {
        Tasks.remove(taskId);
    },
    setCheck: function(taskId, setCheck) {
        Tasks.update(taskId, {$set: { checked: setCheck}});
    }
});

// if (Meteor.isServer) {
//     Meteor.startup(function () {
//     // code to run on server at startup
//         if (Tasks.find().count() == 0) {
//             var text = "this is task ";
//             for (var i = 1; i < 5; i++)
//                 Tasks.insert({
//                     text: text+i.toString(),
//                     date: new Date()
//                 });
//         }
//     });
// }
