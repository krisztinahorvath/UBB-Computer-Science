package com.example.recipejournal.screens

import androidx.compose.foundation.clickable
import androidx.compose.foundation.interaction.MutableInteractionSource
import androidx.compose.foundation.interaction.collectIsPressedAsState
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import com.example.recipejournal.viewmodels.RecipeViewModel
import com.example.recipejournal.models.Recipe
import com.example.recipejournal.viewmodels.SelectedRecipeViewModel
import android.util.Log


@Composable
fun RecipeListScreen(
    navController: NavHostController,
    viewModel: RecipeViewModel,
    selectedRecipeViewModel: SelectedRecipeViewModel
) {
    val recipes = viewModel.getRecipes()
    var selectedRecipe by remember { mutableStateOf<Recipe?>(null) }
    var showDeleteDialog by remember { mutableStateOf(false) }

    LazyColumn {
        item {
            Text(
                text = "Recipe Journal",
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(20.dp),
                textAlign = TextAlign.Center,
                fontSize = 30.sp,
                fontWeight = FontWeight.ExtraBold,
                fontFamily = FontFamily.Cursive
            )
        }

        item {
            Row(
                modifier = Modifier.fillMaxWidth(),
                horizontalArrangement = Arrangement.SpaceBetween
            ) {
                IconButton(
                    onClick = { navController.navigate(RecipeNavigation.RECIPE_CREATE) },
                    modifier = Modifier
                        .padding(8.dp)
                        .size(48.dp)
                ) {
                    Icon(
                        imageVector = Icons.Default.Add,
                        contentDescription = "Add Recipe",
                        modifier = Modifier.size(35.dp)
                    )
                }
            }
        }

        items(recipes) { recipe ->
            RecipeItem(
                recipe = recipe,
                onItemClick = {
                    selectedRecipeViewModel.selectedRecipeId = recipe.id
                    navController.navigate(RecipeNavigation.RECIPE_DETAILS)
                },
                onDeleteClick = {
                    selectedRecipe = recipe
                    showDeleteDialog = true
                }
            )

            if (showDeleteDialog && recipe == selectedRecipe) {
                RecipeDeletePopUp(
                    onDeleteConfirmed = {
                        selectedRecipe?.let { recipe ->
                            viewModel.deleteRecipe(recipe.id)
                        }
                        selectedRecipe = null
                        showDeleteDialog = false
                    },
                    onCancel = {
                        selectedRecipe = null
                        showDeleteDialog = false
                    }
                )
            }
        }
    }
}

@Composable
fun RecipeItem(
    recipe: Recipe,
    onItemClick: () -> Unit,
    onDeleteClick: () -> Unit
) {
    val interactionSource = remember { MutableInteractionSource() }
    val isPressed by interactionSource.collectIsPressedAsState()

    Card(
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp)
            .clickable(
                interactionSource = interactionSource,
                indication = null
            ) {
                if (isPressed) {
                    onDeleteClick()
                } else {
                    onItemClick()
                }
            }
    ) {
        Surface(
            modifier = Modifier.fillMaxSize(),
            color = if (isPressed) Color(0xFFA9BEC9) else Color(0xFFBFCCD6)
        ) {
            Column(
                modifier = Modifier
                    .padding(16.dp)
                    .fillMaxWidth()
            ) {
                Text(
                    text = recipe.name,
                    fontSize = 20.sp,
                    fontWeight = FontWeight.Bold
                )

                Spacer(modifier = Modifier.height(8.dp))

                Text("Preparation Time: ${recipe.time} minutes")
                Text("Servings: ${recipe.servings}")
            }
        }
    }
}
