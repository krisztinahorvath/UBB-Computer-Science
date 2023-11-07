package com.example.recipejournal.viewmodels

import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.snapshots.SnapshotStateList
import androidx.lifecycle.ViewModel
import com.example.recipejournal.models.Recipe
import java.util.concurrent.atomic.AtomicInteger

class RecipeViewModel : ViewModel() {
    private var recipes = mutableStateListOf<Recipe>();
    private val uniqueId = AtomicInteger(100);

    fun getRecipes(): SnapshotStateList<Recipe> {
        return recipes;
    }

    fun getRecipeById(recipeId: Int): Recipe {
        val index = recipes.indexOfFirst { it.id == recipeId }
        return recipes[index]
    }

    fun addRecipe(recipe: Recipe){
        val newRecipe = recipe.copy(id = uniqueId.getAndIncrement())
        recipes.add(newRecipe);
    }

    fun updateRecipe(recipe: Recipe){
        val index = recipes.indexOfFirst { it.id == recipe.id }
        if (index != -1)
            recipes[index] = recipe;
    }

    fun deleteRecipe(recipeId: Int){
        recipes.removeIf{it.id == recipeId}
    }

    init{
        val initRecipes = listOf(
            Recipe(
                id = 1,
                name = "Classic Spaghetti Bolognese",
                ingredients = "Spaghetti, Ground Beef, Onion, Garlic, Tomatoes, Tomato Paste, Red Wine, Olive Oil, Basil, Parmesan Cheese",
                directions = "1. Sauté onions and garlic. 2. Brown ground beef. 3. Add tomatoes, paste, and wine. 4. Simmer and serve over spaghetti.",
                time = 45,
                servings = 4
            ),
            Recipe(
                id = 2,
                name = "Grilled Chicken Caesar Salad",
                ingredients = "Chicken Breasts, Romaine Lettuce, Croutons, Caesar Dressing, Parmesan Cheese",
                directions = "1. Grill chicken. 2. Toss lettuce, croutons, and dressing. 3. Top with grilled chicken and Parmesan.",
                time = 30,
                servings = 2
            ),
            Recipe(
                id = 3,
                name = "Mushroom Risotto",
                ingredients = "Arborio Rice, Mushrooms, Onion, Garlic, White Wine, Chicken Broth, Parmesan Cheese",
                directions = "1. Sauté onions and garlic. 2. Add rice and wine. 3. Gradually add broth. 4. Stir in mushrooms and cheese.",
                time = 35,
                servings = 3
            ),
            Recipe(
                id = 4,
                name = "Vegan Black Bean Chili",
                ingredients = "Black Beans, Onion, Bell Peppers, Tomatoes, Chili Powder, Cumin, Garlic, Vegetable Broth",
                directions = "1. Sauté onions and garlic. 2. Add peppers, beans, tomatoes, and spices. 3. Simmer with vegetable broth.",
                time = 40,
                servings = 6
            ),
            Recipe(
                id = 5,
                name = "Homemade Margherita Pizza",
                ingredients = "Pizza Dough, Tomatoes, Fresh Mozzarella, Fresh Basil, Olive Oil",
                directions = "1. Roll out dough. 2. Top with tomatoes, cheese, and basil. 3. Bake until crust is golden.",
                time = 25,
                servings = 2
            ),
            Recipe(
                id = 6,
                name = "Lemon Garlic Shrimp Scampi",
                ingredients = "Shrimp, Linguine, Lemon Juice, Garlic, White Wine, Butter, Parsley",
                directions = "1. Sauté garlic. 2. Add shrimp, wine, and lemon juice. 3. Toss with cooked linguine.",
                time = 35,
                servings = 4
            ),
            Recipe(
                id = 7,
                name = "Thai Green Curry",
                ingredients = "Chicken, Green Curry Paste, Coconut Milk, Bamboo Shoots, Red Bell Peppers, Thai Basil",
                directions = "1. Cook chicken. 2. Add curry paste, coconut milk, and vegetables. 3. Simmer and serve with Thai basil.",
                time = 45,
                servings = 4
            ),
            Recipe(
                id = 8,
                name = "Spinach and Feta Stuffed Chicken Breast",
                ingredients = "Chicken Breasts, Spinach, Feta Cheese, Garlic, Olive Oil",
                directions = "1. Sauté garlic and spinach. 2. Stuff chicken with spinach and feta. 3. Bake until chicken is cooked.",
                time = 50,
                servings = 2
            ),
            Recipe(
                id = 9,
                name = "Beef and Broccoli Stir-Fry",
                ingredients = "Beef Strips, Broccoli, Garlic, Soy Sauce, Ginger, Rice",
                directions = "1. Sear beef. 2. Stir-fry with garlic, ginger, and broccoli. 3. Serve over rice.",
                time = 30,
                servings = 3
            ),
            Recipe(
                id = 10,
                name = "Creamy Tomato Basil Soup",
                ingredients = "Tomatoes, Onion, Garlic, Fresh Basil, Cream, Butter, Vegetable Broth",
                directions = "1. Sauté onions and garlic. 2. Add tomatoes and broth. 3. Blend with basil, cream, and butter.",
                time = 35,
                servings = 4
            )
        )
        recipes.addAll(initRecipes)
    }
}

