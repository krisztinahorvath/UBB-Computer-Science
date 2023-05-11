
import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-document-browser',
  templateUrl: './document-browser.component.html',
  styleUrls: ['./document-browser.component.css']
})
export class DocumentBrowserComponent implements OnInit {
  types: string[] = [];
  formats: string[] = [];
  selectedType: string = '';
  selectedFormat: string = '';
  documents: any[] = [];
  filterUsed: string = '';
  previousFilter: string = '';

  constructor(private http: HttpClient) { }

  ngOnInit(): void {
    this.populateSelectType();
    this.populateSelectFormat();
  }

  populateSelectType() {
    this.http.get<any[]>('http://localhost/lab7/php/getByType.php?type=')
      .subscribe((data: any) => {
        this.types = data.map((item: { type: any; }) => item.type);
      });
  }

  populateSelectFormat() {
    this.http.get<any[]>('http://localhost/lab7/php/getByFormat.php?format=')
      .subscribe(data => {
        this.formats = data.map(item => item.format);
      });
  }

  populateTable(link: string) {
    this.http.get<any[]>(link)
      .subscribe(data => {
        this.documents = data;
      });
  }

  onTypeChange() {
    const link = "http://localhost/lab7/php/getByType.php?type=" + this.selectedType;
    this.documents = [];
    this.populateTable(link);
    this.selectedFormat = '';
    this.previousFilter = this.filterUsed;
    this.filterUsed = "Previous filter - Type: " + this.selectedType;
  }

  // onTypeAdd() {
  //   const newType = this.selectedType;
  //   this.types.push(newType);
  //   this.selectedType = newType;
  // }

  onFormatChange() {
    const link = "http://localhost/lab7/php/getByFormat.php?format=" + this.selectedFormat;
    this.documents = [];
    this.populateTable(link);
    this.selectedType = '';
    this.previousFilter = this.filterUsed;
    this.filterUsed = "Previous filter - Format: " + this.selectedFormat;
  }

  // onFormatAdd() {
  //   const newFormat = this.selectedFormat;
  //   this.formats.push(newFormat);
  //   this.selectedFormat = newFormat;
  // }
}