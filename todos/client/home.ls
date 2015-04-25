Meteor.startup !->
	Session.set-default 'state', 'SignIn'

if Meteor.is-client
	Template.body.helpers {
		"state": ->
			Session.get 'state'
		"stateIs": (state)->
			return state is Session.get 'state'
	}

	Template.body.events {
		"click .SignIn": ->
			if Session.equals 'state', 'SignIn'
				name = ($ '#username')[0].value
				pw = ($ '#password')[0].value
				Meteor.login-with-password name, pw, (err)!->
					Session.set 'state', 'listview'
					console.log err if err
			else
				Session.set 'state', 'SignIn'
			return false

		"click .Register": !->
			if Session.equals 'state', 'Register'
				role = if $('#student')[0].checked then 'student' else 'teacher'
				Accounts.create-user {
					username: ($ '#username')[0].value
					password: ($ '#password')[0].value
					profile:
						role: role
				}, (err)!-> console.log err if err
			else
				Session.set 'state', 'Register'

		"click .LogOut": !->
			Meteor.logout (err)!-> console.log err if err
	}
