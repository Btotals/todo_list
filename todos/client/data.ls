Assignments = new Mongo.Collection "assignments"
Homeworks = new Mongo.Collection "homeworks"

if Meteor.is-client
	Template.listview.helpers {
		"roleIsTeacher": ->
			return Meteor.user().profile.role is 'teacher'
			# Assignments.find
	}