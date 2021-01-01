#include <sys/stat.h>
#include <sys/types.h>

void dump_read(core_t *core, db_t *db, int32_t i, const char *batch_dir) {

    char read_dir[150];
    snprintf(read_dir, sizeof(read_dir), "%s/%d", batch_dir, i);
    mkdir(read_dir, 0700);
    char filename[200];
    FILE *fp;

    // db->n_event_align_pairs[i]
    snprintf(filename, sizeof(filename), "%s/%s", read_dir,
             "n_event_align_pairs[i].dat");
    fp = fopen(filename, "w");
    fwrite(&(db->n_event_align_pairs[i]), sizeof(int32_t), 1, fp);
    fclose(fp);

    // db->event_align_pairs - out_2
    snprintf(filename, sizeof(filename), "%s/%s", read_dir,
             "event_align_pairs.dat");
    fp = fopen(filename, "w");
    int32_t pairs = db->n_event_align_pairs[i];
    fwrite(db->event_align_pairs[i], sizeof(AlignedPair), pairs, fp);
    fclose(fp);

    // db->read[i] - sequence
    snprintf(filename, sizeof(filename), "%s/%s", read_dir, "read[i].dat");
    fp = fopen(filename, "w");
    // fprintf(stderr, "\n\n\nlast  char:%c\n\n\n\n",
    // db->read[i][db->read_len[i]]);
    fwrite(db->read[i], sizeof(char), db->read_len[i], fp); // without null
    fclose(fp);

    // db->read_len[i] - sequence_len
    snprintf(filename, sizeof(filename), "%s/%s", read_dir, "read_len[i].dat");
    fp = fopen(filename, "w");
    fwrite(&(db->read_len[i]), sizeof(int32_t), 1, fp);
    fclose(fp);

    // db->et[i] - events
    snprintf(filename, sizeof(filename), "%s/%s", read_dir, "et[i].dat");
    fp = fopen(filename, "w");
    fwrite(&(db->et[i]), sizeof(event_table), 1, fp);
    size_t n_events = db->et[i].n;
    fwrite(db->et[i].event, sizeof(event_t), n_events, fp);
    fclose(fp);

    // db->scalings[i] - scaling
    snprintf(filename, sizeof(filename), "%s/%s", read_dir, "scalings[i].dat");
    fp = fopen(filename, "w");
    fwrite(&(db->scalings[i]), sizeof(scalings_t), 1, fp);
    fclose(fp);

    // db->f5[i]->sample_rate - sample_rate
    snprintf(filename, sizeof(filename), "%s/%s", read_dir,
             "f5[i].sample_rate.dat");
    fp = fopen(filename, "w");
    fwrite(&(db->f5[i]->sample_rate), sizeof(float), 1, fp);
    fclose(fp);
}

void dump_one_read(core_t *core, db_t *db, int32_t read_i) {

    const char *dump_dir = "dump_test";

    mkdir(dump_dir, 0700);

    char batch_dir[50];
    snprintf(batch_dir, sizeof(batch_dir), "%s/%d", dump_dir, db->batch_no);
    mkdir(batch_dir, 0700);
    // char filename[100];
    // FILE *fp;

    // for (int i = 0; i < db->n_bam_rec; i++) {
    dump_read(core, db, read_i, batch_dir);
    // }
}

void dump_batch(core_t *core, db_t *db) {

    const char *dump_dir = "dump_test";
    mkdir(dump_dir, 0700);

    char batch_dir[50];
    snprintf(batch_dir, sizeof(batch_dir), "%s/%d", dump_dir, db->batch_no);
    mkdir(batch_dir, 0700);
    char filename[100];
    FILE *fp;

    // db->n_bam_rec
    snprintf(filename, sizeof(filename), "%s/%s", batch_dir, "n_bam_rec.dat");
    fp = fopen(filename, "w");
    fwrite(&(db->n_bam_rec), sizeof(int32_t), 1, fp);
    fclose(fp);

    // core->model - models
    snprintf(filename, sizeof(filename), "%s/%s", batch_dir, "model.dat");
    fp = fopen(filename, "w");
    fwrite(core->model, sizeof(model_t), NUM_KMER, fp);
    fclose(fp);

    for (int32_t read_i = 0; read_i < db->n_bam_rec; read_i++) {
        dump_read(core, db, read_i, batch_dir);
    }
}