Assignments = new Mongo.Collection "assignments"
Homeworks = new Mongo.Collection "homeworks"

if Meteor.is-client
	Template.listview.helpers {
		"stateIs": (state)->
			state is Session.get 'state'
		"roleIsTeacher": ->
			Meteor.user!.profile.role is 'teacher'
		"roleIsStudent": ->
			Meteor.user!.profile.role is 'student'
	}

	Template.listview.events {
		"submit .assign": (event) ->
			assignment = $ event.target.children[0]
			teacher-name = Meteor.user!.username
			ass-name = assignment.find '#ass-name' .val!
			ass-require = assignment.find '#ass-require' .val!
			ass-deadline = assignment.find '#ass-deadline' .val!
			Assignments.insert {
				teacher-name: teacher-name
				owner: Meteor.user!._id
				ass-name: ass-name
				ass-require: ass-require
				ass-deadline: ass-deadline
				create-at: new Date!
			}, (err) !-> console.log err if err
			false
	}

	Template.assign.helpers {
		"assignments": ->
			Assignments.find owner: Meteor.user!._id, { sort: create-at: -1 }

	}

	Template.submit.helpers {
		"assignments": ->
			Assignments.find {}, { sort: create-at: -1 }
	}

	Template.assignment.events {
		"click .show-detail": !->
			Session.set 'state', 'detail'
	}
