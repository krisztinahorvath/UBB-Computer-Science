# Lab 3 assignment

**Points**: 2

**Deadline**: Week 4

**Last chance deadline and penalties**: Week 6, -0.5 points / week delayed

----

Continue working on the application from the previous assignment. Push your project to this repository.

You will need to:
- Add a **many to many** relation between `2` entities. This should be added as a separate entity containing the two related entities or their IDs and at least 2 additional attributes. For example: `Transaction` with `Product` and `Client` as the related entities and `Date` and `Volume` as the additional attributes.
- Make sure all of your entities are part of at least one `1 to 1`, `1 to many` or `many to many` relation.
- Add CRUD for all entities.
- Add at least `10` realistic-looking records for each of your models / tables.
- Use Trello or ClickUp and set up a Kanban board (with at least `Todo`, `Doing`, `Done` or equivalent lists). You will need to update this for all functionalities you do from now on. Your lab instructor will give you feedback on how to improve its setup.
- Create a UML diagram for your application and a database diagram for your database. 
- Add a statistical report involving two entities. For example: show all movies ordered by the average age of their actors. Such reports **need** to show the computed field: the average age of the actors in this case. You probably want to use a `DTO` class for this.

For this and all future assignments, unless otherwise specified, you are not allowed to write any raw SQL queries: it must all be done through an ORM.
