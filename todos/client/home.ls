Meteor.startup !->
	Session.set-default 'state', 'SignIn'
	Session.set-default 'hasErr', false


if Meteor.is-client
	Template.err-message.helpers {
		"hasErr": ->
			Session.get 'hasErr'
		"errMessage": ->
			Session.get 'errMessage'
	}

	Template.login.helpers {
		"state": ->
			Session.get 'state'
		"stateIs": (state)->
			state is Session.get 'state'
	}

	Template.register.helpers {
		"state": ->
			Session.get 'state'
		"stateIs": (state)->
			state is Session.get 'state'
	}

	Template.body.events {
		"click .SignIn": ->
			if Session.equals 'state', 'SignIn'
				name = ($ '#username')[0].value
				pw = ($ '#password')[0].value
				Meteor.login-with-password name, pw, (err)!->
					if err
						console.log err
						Session.set 'hasErr', true
						Session.set 'errMessage', err.message
					else Session.set 'state', 'listview'
			else
				Session.set 'state', 'SignIn'
			false

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
			Meteor.logout (err)!->
				console.log err if err
				Session.set 'state', 'SignIn'
	}
