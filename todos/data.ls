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
			assignment = $ event.target.children.0
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
			assignment.find '#ass-name' .val ''
			assignment.find '#ass-require' .val ''
			assignment.find '#ass-deadline' .val ''
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
			Session.set 'assignmentId', @_id
	}

	Template.detail.helpers {
		"roleIsTeacher": ->
			Meteor.user!.profile.role is 'teacher'
		"roleIsStudent": ->
			Meteor.user!.profile.role is 'student'
		"homeworks": ->
			Homeworks.find { assignment-id: Session.get 'assignmentId' }
		"ass": ->
			Assignments.find { _id: Session.get 'assignmentId' }
		"hw": ->
			Homeworks.find-one {
				student-name: Meteor.user!.username
				assignment-id: Session.get 'assignmentId'
			}
	}

	Template.detail.events {
		"click .submit": !->
			ass-deadline = Assignments.find-one {_id: Session.get 'assignmentId'} .ass-deadline
			ad = new Date ass-deadline
			if new Date! > ad
				alert '已经过了截止时间，不能再修改！'
				Session.set 'state', 'listview'
				return
			content = $ '#cont' .val!
			if Homeworks.find { assignment-id: Session.get 'assignmentId' } .count! is 0
				Homeworks.insert {
					assignment-id: Session.get 'assignmentId'
					student-name: Meteor.user!.username
					content: content
					update-at: new Date!
					grade: '未评分'
				}
			else
				Meteor.call 'updateHomework', Session.get('assignmentId'), content
			Session.set 'state', 'listview'
		"click .return": !->
			Session.set 'state', 'listview'
		"click .assignment-detail": !->
			Session.set 'homeworkId', @_id
			Session.set 'state', 'assignment-detail'
	}

	Template.assignment-detail.helpers {
		"assignment": ->
			Assignments.find-one {_id: Session.get 'assignmentId'}
		"homework": ->
			Homeworks.find-one {_id: Session.get 'homeworkId'}
	}

	Template.assignment-detail.events {
		"click .submit": !->
			rank = $ '#rank' .val!
			Meteor.call 'updateGrade', Session.get('assignmentId'), rank
			Session.set 'state', 'assignment-detail'
		"click .return-to-detail": !->
			Session.set 'state', 'assignment-detail'
	}

Meteor.methods {
	update-homework: (assId, cont)!->
		Homeworks.update { assignment-id: assId }, { $set: { content: cont, update-at: new Date! } }
	update-grade: (assId, rank)!->
		Homeworks.update { assignment-id: assId }, { $set: { grade: rank, update-at: new Date! } }
}

