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
		"click .SignIn": !->
			if Session.equals('state', 'SignIn')
				...
			else
				Session.set 'state', 'SignIn'

		"click .Register": !->
			if Session.equals('state', 'Register')
				...
			else
				Session.set 'state', 'Register'
	}
