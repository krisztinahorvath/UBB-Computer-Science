import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { HttpClient, HttpHeaders } from '@angular/common/http';

@Component({
  selector: 'app-document-add',
  templateUrl: './document-add.component.html',
  styleUrls: ['./document-add.component.css']
})
export class DocumentAddComponent implements OnInit {
  title: string = '';
  author: string = '';
  numberOfPages: number | undefined;
  type: string = '';
  format: string = '';

  constructor(private router: Router, private http: HttpClient) { }

  ngOnInit(): void {
  }

  addDocument() {
    if (!this.title) {
      alert('Please enter a title.');
      return;
    }

    if (this.numberOfPages !== undefined && isNaN(this.numberOfPages)) {
      alert('Please enter a valid number for the number of pages.');
      return;
    } else if (this.numberOfPages !== undefined && this.numberOfPages <= 0) {
      alert('Please enter a non-null positive number for the number of pages.');
      return;
    }

    if(!this.format){
      alert('Please enter a format.');
      return;
    }

    const postData = {
      title: this.title,
      author: this.author,
      numberOfPages: this.numberOfPages,
      type: this.type,
      format: this.format
    };

    const httpOptions = {
      headers: new HttpHeaders({
        'Content-Type': 'application/json'
      })
    };

    this.http.post<any>('http://localhost/lab7/php/add.php', postData, httpOptions)
      .subscribe(
        response => {
          alert(response.message);
          this.router.navigate(['/home']);
        },
        error => {
          alert(error.error.message);
        }
      );
  }
}