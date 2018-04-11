package mlib

import "testing"

func TestOps(t *testing.T){
	mm := NewMusicManager()
	if mm == nil {
		t.Error("NewMusicManager failed")
	}

	if mm.Len() != 0 {
		t.Error("NewMusicManager failed, not empty")	
	}

	m0 := &MusicEntry{
		"1", "i_am_happy", "none", "/home/he_liangbin/test/golang/src/music", "MP3"}

	mm.Add(m0)

	if mm.Len() != 1{
		t.Error("MusicManager.Add failed")
	}

	m := mm.Find(m0.Name)
	if m == nil {
		t.Error("MusicManager.Find failed")
	}

	m, err := mm.Get(0)
	if m == nil {
		t.Error("MusicManager.Get failed")
	}

	m = mm.Remove(0)
	if m==nil || mm.Len() != 0 {
		t.Error("MusicManager.Remove failed", err)
	}	
}

