import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DocumentRemoveComponent } from './document-remove.component';

describe('DocumentRemoveComponent', () => {
  let component: DocumentRemoveComponent;
  let fixture: ComponentFixture<DocumentRemoveComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [DocumentRemoveComponent]
    });
    fixture = TestBed.createComponent(DocumentRemoveComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
