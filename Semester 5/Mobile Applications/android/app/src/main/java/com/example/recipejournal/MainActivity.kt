package com.example.recipejournal

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.runtime.Composable
import androidx.compose.ui.tooling.preview.Preview
import com.example.recipejournal.screens.RecipeNavigation
import com.example.recipejournal.ui.theme.RecipeJournalTheme
import com.example.recipejournal.viewmodels.RecipeViewModel

class MainActivity : ComponentActivity() {
    private val viewModel = RecipeViewModel()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            RecipeJournalTheme {
                RecipeNavigation(viewModel)
            }
        }
    }
}
