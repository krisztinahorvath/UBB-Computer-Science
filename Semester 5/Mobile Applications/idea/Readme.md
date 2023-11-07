## 1. Short Description

Recipe Journal is a user-friendly mobile app designed for food enthusiasts and home cooks. It simplifies the process of creating and managing 
your favorite recipes. With fields for recipe name, ingredients, step-by-step directions, preparation time, and serving size, 
this app provides a convenient way to keep your culinary creations organized. Recipe Journal serves as your digital cookbook, elegantly organizing 
your recipes in a visually appealing manner, ensuring that your culinary creations are not only easily accessible but also presented in an 
understandable format.

## 2. Domain details.
The app should manage recipes having the following properties:
- name -> for the name of the recipe
- ingredients -> all the ingredients it takes to make the recipe
- directions -> for the directions of making the recipe
- time -> prepartion time of the recipe
- servings -> how many servings does the recipe make

## 3. Details of the CRUD operations:
- for creating a new recipe, the user will be asked to fill in a couple fields regarding the recipe details, such as: the name, ingredients, 
directions, time and servings of the recipe. The name and ingredients of the recipe
are mandatory, if the user wants to change or add more details later, they can do so by updating the recipe.
- for updating a recipe, the user can change any of the fields of the recipe(name, ingredients, directions, time, servings)
- for deleting a recipe, the user can select a recipe and choose the delete option, after which the recipe is removed from their list of recipes.

## 4. Persistance details

The mobile app will have a local database and a server-side database, making sure that the user can access their recipes from different devices.
When the user wants to create/update/delete a recipe, all operations will be saved both locally and on the server.

## 5. Details on what is happening when the device is offline:
- when viewing all the recipes: data will be taken from the local database, but the user will be notified that the server connection is down
- when adding/updating/deleting a recipe: the data will be persisted in the local database and when the device is online again the data will be saved on the server too
