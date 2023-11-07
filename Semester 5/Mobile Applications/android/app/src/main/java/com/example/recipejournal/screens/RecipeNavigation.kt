package com.example.recipejournal.screens

import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.recipejournal.viewmodels.RecipeViewModel
import com.example.recipejournal.viewmodels.SelectedRecipeViewModel

object RecipeNavigation {
    const val RECIPE_LIST = "recipeList"
    const val RECIPE_DETAILS = "recipeDetails"
    const val RECIPE_CREATE = "recipeCreate"
    const val RECIPE_UPDATE = "recipeUpdate"
    const val RECIPE_DELETE = "recipeDelete"
}

@Composable
fun RecipeNavigation(viewModel: RecipeViewModel) {
    val navController = rememberNavController()
    val selectedRecipeViewModel = remember { SelectedRecipeViewModel() }

    NavHost(navController = navController, startDestination = RecipeNavigation.RECIPE_LIST) {
        composable(RecipeNavigation.RECIPE_LIST) {
            RecipeListScreen(navController, viewModel, selectedRecipeViewModel)
        }
        composable(RecipeNavigation.RECIPE_CREATE) {
            RecipeCreate(viewModel, onRecipeCreated = {navController.popBackStack()}, navController)
        }
        composable(RecipeNavigation.RECIPE_DETAILS) {
            RecipeDetails(viewModel, selectedRecipeViewModel, navController)
        }
        composable(RecipeNavigation.RECIPE_UPDATE){
            RecipeUpdateScreen(viewModel, selectedRecipeViewModel, navController)
        }
    }
}