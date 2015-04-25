Assignments = new Mongo.Collection "assignments"
Homeworks = new Mongo.Collection "homeworks"

if Meteor.is-client
	Template.listview.helper {
		"assignments": ->

			# Assignments.find
	}