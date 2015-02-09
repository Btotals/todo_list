Tasks = new Mongo.Collection 'tasks'

if Meteor.is-client
  Template.body.helpers(
    tasks: ->
      if Session.get 'hideCompleted'
        then Tasks.find {checked: {$ne: true}} {sort: {date: -1}}
        else Tasks.find {} {sort: {date: -1}}
    hide-completed: ->
      Session.get 'hideCompleted'
    incomplete-count: ->
      (Tasks.find {checked: {$ne: true}}) .count!
  )

  Template.body.events(
    'submit .new-task': (event)!->
      target = event.target or event.src-element
      text = target.0.value
      Tasks.insert(
        text: text
        date: new Date!
        owner: Meteor.user-id!
        username: Meteor.user!.username
      )
    'change .hide-completed input': !->
      Session.set "hideCompleted" event.target.checked
  )

  Template.task.events(
    'click .toggle-checked': !->
      Tasks.update @_id, {$set: {checked: !@checked}}
    'click .delete': !->
      if @checked then Tasks.remove @_id
  )

  Accounts.ui.config {password-signup-fields: 'USERNAME_ONLY'}
